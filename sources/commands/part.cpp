#include "Server.hpp"

void Server::part(std::string msg, int index)
{
	(void) index;

	User &user = this->GetUserByFd(this->_lst_fd[index].fd);
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
	std::vector<User *> test = channel.getVecUsers();
	std::vector<User *>::iterator ite = test.end();
	std::cout << "[TEST]" << std::endl;
	for (std::vector<User *>::iterator it = test.begin(); it != ite; ++it)
	{
		std::cout << "USER : " << (*it)->getNickname() << " " << user.getNickname() << std::endl;
		//if ((*it)->getNickname() == user.getNickname())
		//{
		//	test.erase(it);
		//	break;
		//}
	}
	std::cout << "[TEST]" << std::endl;
	//if (it == ite)
	//{
	//	//ERR_NOTONCHANNEL
	//}
	std::string message = HEADER_CMD(user) + "PART " + channel_name + " " + reason + "\r\n";
	sendUserList(channel);
	std::cout << "[TEST]" << std::endl;
}