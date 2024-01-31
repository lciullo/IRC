#include "Server.hpp"

void sendUserList(Channel channel)
{
	std::string message;

	for (size_t i = 0; i < channel.getVecUsers().size(); i++)
	{
		User &user2 = *channel.getVecUsers()[i];
		for (size_t j = 0; j < channel.getVecUsers().size(); j++)
		{
			User userToSend = *channel.getVecUsers()[j];
			message = HEADER_CMD(userToSend) + "353 " + userToSend.getNickname() + " = " + channel.getName() + " :";
			if (channel.getLstUsers()[&user2] == OPERATOR)
				message.append("@");
			else if (channel.getLstUsers()[&user2] == VOICE)
				message.append("+");
			message.append(user2.getNickname() + "\r\n");
			send(userToSend.getFd(), message.c_str(), message.size(), 0);
		}
	}
	for (size_t j = 0; j < channel.getVecUsers().size(); j++)
	{
		User userToSend = *channel.getVecUsers()[j];
		message = HEADER_CMD(userToSend) + "366 " + userToSend.getNickname() + " " + channel.getName() + " :End of /NAMES list\r\n";
		send(channel.getVecUsers()[j]->getFd(), message.c_str(), message.size(), 0);
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
	std::string arg_channel = cmd[1];
	std::vector<std::string> channels_name;
	split_arg(&channels_name, arg_channel);

	std::vector<std::string> channels_key;
	split_arg(&channels_name, arg_channel);
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
			return ;
		}
		std::map<std::string , Channel>::iterator it;
		it = this->_lst_channel.find(channels_name[i]);
		if (it == this->_lst_channel.end())
		{
			Channel new_channel(channels_name[i], &user);
			if (channels_name[i][0] == '#')
				new_channel.addMode('t', "no param");
			std::cout << "create channel " << new_channel.getName() << " by " << user.getNickname() << std::endl;
			this->_lst_channel[channels_name[i]] = new_channel;
		}
		else
		{
			if (it->second.findUser(&user))
				return ;
			if (!it->second.getPassword().empty())
			{
				std::string key;
				if (i < channels_key.size())
					key = channels_key[i];
				else
				{
					ERR_BADCHANNELKEY(user, channels_name[i]);
					return ;
				}
				if (key != it->second.getPassword())
				{
					ERR_BADCHANNELKEY(user, channels_name[i]);
					return ;
				}
			}
			it->second.addUser(&user);
		}
		Channel channel = this->_lst_channel[channels_name[i]];
		std::string message = HEADER_CMD(user) + "JOIN " + channels_name[i] + "\r\n";
		send(fd, message.c_str(), message.size(), 0);
		sendUserList(channel);
	}
}
