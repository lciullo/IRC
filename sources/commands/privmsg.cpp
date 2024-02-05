#include "Server.hpp"

void Server::privmsg(std::string msg, int fd)
{
	User &sender = this->GetUserByFd(fd);
	size_t ind = msg.find("PRIVMSG");
	std::string dest = msg.substr(ind + 8);
	ind = dest.find(" ");
	dest = dest.substr(0, ind);
	ind = msg.find(":");
	if (ind == std::string::npos)
	{
		ERR_NOTEXTTOSEND(this->_lst_usr[fd]);
		return ;
	}
	std::vector<std::string> lst_dest;
	split_arg(&lst_dest, dest);
	std::string msg_to_send = msg.substr(ind);
	msg_to_send = msg_to_send.substr(0, msg_to_send.size());
	std::cout << "dest : " << dest << " | message to send : " << msg_to_send << std::endl;
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
				std::string message = ":" + this->GetUserByFd(fd).findNickname() + " PRIVMSG " + lst_dest[i] + " " + msg_to_send + "\r\n";
				if (user->findNickname() == this->GetUserByFd(fd).findNickname())
					continue ;
				send(user->getFd(), message.c_str(), message.size(), 0);
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
			send(userToSend.getFd(), message.c_str(), message.size(), 0);
		}
	}
}