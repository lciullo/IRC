#include "Server.hpp"

void Server::part(std::string msg, int index)
{
	(void) index;

	User user = this->GetUserByFd(this->_lst_fd[index].fd);
	int i = msg.find("PART");
	std::string channel_name = msg.substr(i + 5);
	i = channel_name.find(" ");
	channel_name = channel_name.substr(0, i);
	std::string reason = msg.substr(msg.find(":"));
	reason = reason.substr(0, reason.size() - 2); //for remove last \r\n
	std::cout << "[PART] channel : " << channel_name << " | reason : " << reason << " | who : " << user.getNickname() << std::endl;

}