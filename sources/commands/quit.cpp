#include "Server.hpp"
#include "IRC.hpp"
#include <map>
#include <iostream>

void Server::quit(std::string msg, int fd)
{
	std::vector<std::string>	cmd;
	std::string 				reason;
	std::string message;

	split_cmd(&cmd, msg);
	User &user = this->GetUserByFd(fd);
	
	if (cmd.size() == 2)
		reason = cmd[1];
	std::vector<std::string> userChannel = user.getUserChannels();
	std::vector<std::string>::iterator	it;
	for (it = userChannel.begin(); it != userChannel.end(); it++) 
	{
		Channel &channel = this->_lst_channel[*it];
		message = "PART " + channel.getName();
		if (cmd.size() == 2)
			message.append(" " + reason);
		message.append("\r\n");
		this->part(message, fd);
	}
	std::vector<std::string> userChannelInvite = user.getInvite();
	for (it = userChannelInvite.begin(); it != userChannelInvite.end(); it++) 
	{
		Channel &channel = this->_lst_channel[*it];
		channel.deleteUserToWaitlist(user);
	}
	std::cout << RED << "USER QUIT (" << fd << ")" << RESET << std::endl;
	message = HEADER_CMD(user) + "QUIT";
	if (cmd.size() == 2)
		message.append(" " + reason);
	message.append("\r\n");
	send(user.getFd(), message.c_str(), message.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
	deleteUserFromLst(fd);
	closeUserFd(fd);
	return ;
}
