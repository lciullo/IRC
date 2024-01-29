#include "Server.hpp"
#include "IRC.hpp"
#include <map>
#include <iostream>

void Server::quit(int fd)
{
	//1- Get user by fd : 
	(void)fd;
	//Get user 
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
	/*size_t elementsErased = getLstUsr().erase(0,user.getNickname());
	(void)elementsErased;*/
	return ;
}

bool Server::searchChannelInServer(std::string target)
{
	std::map<std::string, Channel>::iterator it = this->_lst_channel.find(target);
	if (it != this->_lst_channel.end())
		return (true);
	return (false);
}