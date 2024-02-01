#include "Server.hpp"

void Server::privmsg(std::string msg, int fd)
{
	int i = msg.find("PRIVMSG");
	std::string dest = msg.substr(i + 8);
	i = dest.find(" ");
	dest = dest.substr(0, i);
	std::cout << "[TEST] priv" << std::endl;
	i = msg.find(":");
	if ((size_t)i == std::string::npos)
	{
		ERR_NOTEXTTOSEND(this->_lst_usr[fd]);
		return ;
	}
	std::string send_msg = msg.substr(msg.find(":"));
	std::cout << "[TEST] priv" << std::endl;
	send_msg = send_msg.substr(0, send_msg.size());
	std::cout << "[TEST] priv" << std::endl;
	std::cout << "dest : " << dest << " | message to send : " << send_msg << std::endl;
	std::cout << "[TEST] priv" << std::endl;
	if (dest[0] == '#' || dest[0] == '&')
	{
		Channel channel = this->_lst_channel[dest];
		for (size_t i = 0; i < channel.getVecUsers().size(); i++)
		{
			User *user = channel.getVecUsers()[i];
			std::string message = ":" + this->GetUserByFd(fd).getNickname() + " PRIVMSG " + dest + " " + send_msg + "\r\n";
			if (user->getNickname() == this->GetUserByFd(fd).getNickname())
				continue ;
			send(user->getFd(), message.c_str(), message.size(), 0);
		}
	}
	else
	{
		User &sender = this->GetUserByFd(fd);
		User &userToSend = this->GetUserByNickname(dest);
		std::string message = HEADER_CMD(sender) + "PRIVMSG " + dest + " " + send_msg + "\r\n";
		send(userToSend.getFd(), message.c_str(), message.size(), 0);
	}
}