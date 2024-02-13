#include "Server.hpp"

bool Server::switchNickCase(User &user, std::string msg, int fd)
{
	std::vector<std::string> cmd;
	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "NICK");
		return (false);
	}
	if (user.getLevel() == 0)
	{
		ERR_NOTREGISTERED(user);
		return (false);
	}
	if (nick(user, findNickname(msg), fd) == false)
	{
		if (user.getLevel() >= 1)
			return (false);
	}
	user.setNickname(cmd[1]);
	return (true);
}

bool Server::nick(User &user, std::string nickname, int fd)
{
	std::string toUpdate;
	std::string oldNickname = user.getoldNickname();
	
	if (nickname.empty())
	{
		ERR_NONICKNAMEGIVEN(this->GetUserByFd(fd), nickname);
		return (false);
	}
	if (!isValidNickname(nickname))
	{
		ERR_ERRONEUSNICKNAME(this->GetUserByFd(fd), nickname);
		return (false);
	}
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getNickname() == nickname)
		{
			ERR_NICKNAMEINUSE(this->GetUserByFd(fd), nickname);
			if (oldNickname.empty())
				user.setoldNickname(nickname);
			return (false);
		}
	}
	if (oldNickname.empty())
		toUpdate = nickname;
	else
		toUpdate = oldNickname;
 	user.setoldNickname(nickname);
	if (user.getNickname().empty())
	{
		user.addLevel();
	}
	user.setNickname(toUpdate);
	sendStringSocket(fd, RPL_NICK(toUpdate, user.getUsername(), nickname));
	sendNewNickname(user, toUpdate, nickname); 
	return (true);
}

bool Server::isValidNickname(std::string nickname)
{
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if ((nickname[i] == '#') || (nickname[i] == '&') || (nickname[i] == ':') \
		|| (nickname[i] == ' ') || (nickname[i] == '\t') || (nickname[i] == '\v') \
		|| (nickname[i] == '\n') || (nickname[i] == '\r') || (nickname[i] == '\f'))
			return (false);
	}

	return (true);
}

std::string Server::findNickname(std::string msg)
{
	std::istringstream	iss(msg);
	std::string			line;
	std::string			nickname;
	while (std::getline(iss, line)) 
	{
		size_t pos = line.find("NICK");
		if (pos != std::string::npos) {
			nickname = line.substr(5);
			nickname = nickname.substr(0, nickname.size());
		}
	}
	return (nickname);
}

void Server::sendNewNickname(User &user, std::string toUpdate, std::string nickname)
{
	std::vector<std::string> userChannelLst = user.getUserChannels();
	std::vector<std::string>::iterator	it;
	for (it = userChannelLst.begin(); it != userChannelLst.end(); it++) 
	{
		if (searchChannelInServer(*it))
		{	
			Channel &channel = this->_lst_channel[*it];
			sendInEachChannel(channel, user, toUpdate, nickname);
		}

	}
	return ;
}

void Server::sendInEachChannel(Channel &channel, User &user, std::string toUpdate,std::string nickname)
{
	for (size_t i = 0; i < channel.getVecUsers().size(); i++)
	{
		
		User userToSend = *channel.getVecUsers()[i];
		if (toUpdate!= userToSend.getNickname())
		{
			sendStringSocket(channel.getVecUsers()[i]->getFd(), RPL_NICK(toUpdate, user.getUsername(), nickname));
		}
	}
	return ;
}