#include "Server.hpp"
#include "IRC.hpp"
#include <map>
#include <iostream>

void Server::quit(std::string msg, int fd)
{
	User &user = GetUserByFd(fd); 
	
	int i = msg.find("QUIT");
	std::string channel_name = msg.substr(i + 5);
	i = channel_name.find(" ");
	std::string reason = msg.substr(msg.find(":"));
	reason = reason.substr(1, reason.size());
	std::cout << "[QUIT] :" << reason << std::endl;
	Channel &channel = this->_lst_channel[channel_name];
	std::string message = HEADER_CMD(user) + "QUIT " + channel_name + " " + reason + "\r\n";
	send(user.getFd(), message.c_str(), message.size(), 0);
	sendUserList(channel);
	
	deleteUserFromChannel(user);
	deleteUserFromLst(fd);
	closeUserFd(fd); 
	return ;
}
