#include "Server.hpp"
#include "Numerics.hpp"

void Server::part(std::string msg, int fd)
{
	std::string reason = "";
	std::vector<std::string> cmd;

	split_cmd(&cmd, msg);
	User &user = this->GetUserByFd(fd);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "PART");
		return ;
	}
	std::string arg_channel = cmd[1];
	std::vector<std::string> channels_name;
	split_arg(&channels_name, arg_channel);
	for (size_t i = 0; i < channels_name.size(); i++)
	{
		std::map<std::string, Channel>::iterator it;
		it=this->_lst_channel.find(channels_name[i]);
		if (it == this->_lst_channel.end())
		{
			ERR_NOSUCHCHANNEL(user, channels_name[i]);
			break ;
		}
		Channel &channel = this->_lst_channel[channels_name[i]];
		if (!channel.findUser(&user))
		{
			ERR_NOTONCHANNEL(user, channels_name[i]);
			break ;
		}
		channel.deleteUser(user);
		std::string message = HEADER_CMD(user) + "PART " + channels_name[i];
		if (cmd.size() > 2)
		{
			reason = cmd[2];
			message.append(" " + reason);
		}
		message.append("\r\n");
		std::cout << "[PART] channel : " << channels_name[i] << " | reason : " << reason << " | who : " << user.getNickname() << std::endl;
		send(user.getFd(), message.c_str(), message.size(), 0);
		user.deleteChannel(channel.getName());
		sendUserList(channel);
		//if last user left channel rm channel of list
	}
}