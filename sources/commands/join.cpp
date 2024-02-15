#include "Server.hpp"
#include <iostream>
#include <ctime>

void sendUserList(Channel channel, User &userToSend)
{
	std::string message;

	for (size_t i = 0; i < channel.getVecUsers().size(); i++)
	{
		User &user2 = *channel.getVecUsers()[i];
		std::cout << RED << channel.getName() << RESET << std::endl;
		message = HEADER_CMD(userToSend) + "353 " + userToSend.getNickname() + " = " + channel.getName() + " :";
		if (channel.getLstUsers()[&user2] == OPERATOR)
			message.append("@");
		else if (channel.getLstUsers()[&user2] == VOICE)
			message.append("+");
		message.append(user2.getNickname() + "\r\n");
		send_msg(userToSend, message);
	}
	message = HEADER_CMD(userToSend) + "366 " + userToSend.getNickname() + " " + channel.getName() + " :End of /NAMES list\r\n";
	send_msg(userToSend, message);
}

void sendJoinToAll(Channel channel, User &user)
{
	std::string message;

	for (size_t i = 0; i < channel.getVecUsers().size(); i++)
	{
		User &userToSend = *channel.getVecUsers()[i];
		if (userToSend.getNickname() == user.getNickname())
			continue ;
		std::cout << RED << channel.getName() << RESET << std::endl;
		message = ":+" + user.getNickname() + "!" + user.getUsername() + " JOIN " + channel.getName() + "\r\n";
		send_msg(userToSend, message);
	}
}

void Server::join(std::string msg, int fd)
{
	std::vector<std::string> cmd;
	User &user = this->GetUserByFd(fd);

	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "JOIN");
		return ;
	}
	if (cmd[1] == "0")
	{
		while (user.getUserChannels().size() != 0)
		{
			this->part("PART " + user.getUserChannels()[0], fd);
		}
		return ;
	}
	std::string arg_channel = cmd[1];
	std::vector<std::string> channels_name;
	split_arg(&channels_name, arg_channel);

	std::vector<std::string> channels_key;
	if (cmd.size() > 2)
	{
		std::string arg_key = cmd[2];
		split_arg(&channels_key, arg_key);
	}
	for (size_t i = 0; i < channels_name.size(); i++)
	{
		if (channels_name[i][0] != '#' && channels_name[i][0] != '&')
		{
			ERR_BADCHANMASK(user, channels_name[i]);
			continue ;
		}
		std::map<std::string , Channel>::iterator it;
		it = this->_lst_channel.find(channels_name[i]);
		if (it == this->_lst_channel.end())
		{
			if (channels_name[i].size() == 1)
			{
				ERR_NOSUCHCHANNEL(user, channels_name[i]);
				continue ;
			}
  			if (channels_name[i].find(7) != std::string::npos) //to find ctrl-g in a channel name
			{
				SIMPLE_MSG(user , "Not good channel name : " + channels_name[i] + " (there is a ctrl-g in)");
				continue ;
			}
			Channel new_channel(channels_name[i], &user);
			if (channels_name[i][0] == '#')
				new_channel.addMode('t', "");
			this->_lst_channel[channels_name[i]] = new_channel;
		}
		else
		{
			Channel &channel = this->_lst_channel[channels_name[i]];
			if (channel.findUser(&user))
				continue ;
			if (channel.getStatus() && !channel.findInWaitList(user))
			{
				ERR_INVITEONLYCHAN(user, channels_name[i]);
				continue ;
			}
			if (!channel.getPassword().empty())
			{
				std::string key;
				if (i < channels_key.size())
					key = channels_key[i];
				else
				{
					ERR_BADCHANNELKEY(user, channels_name[i]);
					continue ;
				}
				if (key != channel.getPassword())
				{
					ERR_BADCHANNELKEY(user, channels_name[i]);
					continue ;
				}
			}
			if (channel.getNbrUserMax() != -1 && channel.getNbrUser() >= channel.getNbrUserMax())
			{
				ERR_CHANNELISFULL(user, channels_name[i]);
				continue ;
			}
			channel.deleteUserToWaitlist(user);
			user.deleteInvite(channel.getName());
			channel.addUser(&user);
		}
		Channel &channel = this->_lst_channel[channels_name[i]];
		std::string message = HEADER_CMD(user) + "JOIN " + channels_name[i] + "\r\n";
		send_msg(user, message);
		if (!channel.getTopic().empty())
			RPL_TOPIC(user, channel.getName(), channel.getTopic());
		RPL_CHANNELMODEIS(user, channel.getName(), channel.getModestring());
		sendUserList(channel, user);
		sendJoinToAll(channel, user);
	}
}
