#include "Server.hpp"
#include "IRC.hpp"
#include <map>
#include <iostream>

void Server::quit(int fd)
{
	User user = GetUserByFd(fd);
	//===================================
	//   delete user from each channel 
	std::vector<std::string> userChannel = user.getUserChannels();
	std::vector<std::string>::iterator	it;
	//search in USER class the channel of user 
	for (it = userChannel.begin(); it != userChannel.end(); it++) 
	{
		//search SERVER class name of channel 
		if (searchChannelInServer(*it))
		{
			//delete user of CHANNEL 	
			Channel &channel = this->_lst_channel[*it];
			channel.deleteUser(user);
		}

	}
	//===================================
	//   delete user from list of user in SERVER class  
	/*std::map<User, int>::iterator it;
	for (it = this->_lst_usr.begin(); it != this->_lst_usr.end(); ++it) 
	{
		std::cout << RED << "in map _lst_usr" << *it << RESET << std::endl;
	}*/
	/*std::map<User, int>::iterator	it2 = this->_lst_usr.find(fd);
	if (it2 != this->_lst_usr.end())
		this->_lst_usr.erase(it2);
		//_nbUsers--;*/
	//===================================
	//   close fd to disconect current user
	close(fd);
	for (size_t i = 0; i < this->_lst_fd.size(); i++)
	{
		if (this->_lst_fd[i].fd == fd) {
			this->_lst_fd.erase(this->_lst_fd.begin() + i);
				break;
		}
	}
	//===================================
	// check reason split this function in many little function 

	// TIMER ?
	return ;
}

bool Server::searchChannelInServer(std::string target)
{
	std::map<std::string, Channel>::iterator it = this->_lst_channel.find(target);
	if (it != this->_lst_channel.end())
		return (true);
	return (false);
}