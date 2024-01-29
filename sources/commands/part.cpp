#include "Server.hpp"

void Server::part(std::string msg, int fd)
{
	(void) fd;

	User &user = this->GetUserByFd(fd);
	int i = msg.find("PART");
	std::string channel_name = msg.substr(i + 5);
	i = channel_name.find(" ");
	channel_name = channel_name.substr(0, i);
	//std::map<std::string, Channel>::iterator *it;
	//it=this->_lst_channel.find(channel_name);
	//if (it == this->_lst_channel.end())
	//{
	//	//ERR_NOSUCHCHANNEL
	//}
	std::string reason = msg.substr(msg.find(":"));
	reason = reason.substr(0, reason.size() - 2); //for remove last \r\n
	std::cout << "[PART] channel : " << channel_name << " | reason : " << reason << " | who : " << user.getNickname() << std::endl;
	Channel &channel = this->_lst_channel[channel_name];
	channel.deleteUser(user);
	std::string message = HEADER_CMD(user) + "PART " + channel_name + " " + reason + "\r\n";
	send(user.getFd(), message.c_str(), message.size(), 0);
	sendUserList(channel);
}