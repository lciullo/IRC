#include "Server.hpp"

void Server::privmsg(std::string msg, int fd)
{
	User &sender = this->GetUserByFd(fd);
	std::vector<std::string> cmd;

	split_cmd(&cmd, msg);
	if (cmd.size() < 3)
	{
		ERR_NEEDMOREPARAMS(sender, "PRIVMSG");
		return;
	}
	if (cmd[2][0] != ':')
	{
		ERR_NOTEXTTOSEND(this->_lst_usr[fd]);
		return ;
	}
	std::string dest = cmd[1];
	std::vector<std::string> lst_dest;
	split_arg(&lst_dest, dest);
	std::string msg_to_send = cmd[2];
	if (msg_to_send.size() <= 1)
		return ;
	for (size_t i = 0; i < lst_dest.size(); i++)
	{
		if (lst_dest[i][0] == '#' || lst_dest[i][0] == '&')
		{
			if (!searchChannelInServer(lst_dest[i]))
			{
				ERR_CANNOTSENDTOCHAN(sender, lst_dest[i]);
				continue ;
			}
			Channel channel = this->_lst_channel[lst_dest[i]];
			if (!channel.findUser(&sender))
			{
				ERR_CANNOTSENDTOCHAN(sender, lst_dest[i]);
				continue ;
			}
			for (size_t j = 0; j < channel.getVecUsers().size(); j++)
			{
				User *user = channel.getVecUsers()[j];
				std::string message = ":" + this->GetUserByFd(fd).getNickname() + " PRIVMSG " + lst_dest[i] + " " + msg_to_send + "\r\n";
				if (user->getNickname() == this->GetUserByFd(fd).getNickname())
					continue ;
				send_msg(*user, message);
			}
		}
		else
		{
			if (!searchUserInServer(lst_dest[i]))
			{
				ERR_NOSUCHNICK(sender, lst_dest[i]);
				continue ;
			}
			User &userToSend = this->GetUserByNickname(lst_dest[i]);
			std::string message = HEADER_CMD(sender) + "PRIVMSG " + lst_dest[i] + " " + msg_to_send + "\r\n";
			send_msg(userToSend, message);
		}
	}
}