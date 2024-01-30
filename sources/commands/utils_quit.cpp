#include "Server.hpp"

void Server::closeUserFd(int fd)
{
	close(fd);
	for (size_t i = 0; i < this->_lst_fd.size(); i++)
	{
		if (this->_lst_fd[i].fd == fd) {
			this->_lst_fd.erase(this->_lst_fd.begin() + i);
				break;
		}
	}
	return ;
}

void Server::deleteUserFromChannel(User user)
{
	std::vector<std::string> userChannel = user.getUserChannels();
	std::vector<std::string>::iterator	it;
	for (it = userChannel.begin(); it != userChannel.end(); it++) 
	{
		if (searchChannelInServer(*it))
		{	
			Channel &channel = this->_lst_channel[*it];
			channel.deleteUser(user);
		}

	}
	return ;
}

bool Server::searchChannelInServer(std::string target)
{
	std::map<std::string, Channel>::iterator it = this->_lst_channel.find(target);
	if (it != this->_lst_channel.end())
		return (true);
	return (false);
}


void Server::deleteUserFromLst(int fd)
{
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getFd() == fd) {
			this->_lst_usr.erase(it->second.getFd());
			break ;
		}
	}
	return ;
}