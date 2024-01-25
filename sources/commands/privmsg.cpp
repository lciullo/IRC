#include "Server.hpp"

void Server::privmsg(std::string msg, int index)
{
	int i = msg.find("PRIVMSG");
	std::string dest = msg.substr(i + 8);
	i = dest.find(" ");
	dest = dest.substr(0, i);
	std::string send_msg = msg.substr(msg.find(":"));
	send_msg = send_msg.substr(0, send_msg.size() - 2); //for remove last \r\n
	std::cout << "dest : " << dest << std::endl;
	if (dest[0] == '#')
	{
		Channel channel = this->_lst_channel[dest];
		for (size_t i = 0; i < channel.getVecUsers().size(); i++)
		{
			User *user = channel.getVecUsers()[i];
			std::string message = ":" + this->GetUserByFd(this->_lst_fd[index].fd).getNickname() + " PRIVMSG " + dest + " " + send_msg + "\n"; //
			if (user->getNickname() == this->GetUserByFd(this->_lst_fd[index].fd).getNickname())
				continue ;
			send(user->getFd(), message.c_str(), message.size(), 0);
		}
	}
	else
	{
		User &sender = this->GetUserByFd(this->_lst_fd[index].fd);
		User &userToSend = this->GetUserByNickname(dest);
		std::string message = HEADER_CMD(sender) + "PRIVMSG " + dest + " " + send_msg + "\r\n";
		std::cout << "TEST : " << message << std::endl;
		send(userToSend.getFd(), message.c_str(), message.size(), 0);
	}
}