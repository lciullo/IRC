#include "Server.hpp"

bool Server::switchNickCase(std::string msg, int fd)
{
	User &user = GetUserByFd(fd);
	std::vector<std::string> cmd;
	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "NICK");
		return (false);
	}
	if (nick(getNickname(msg), fd) == false)
	{
		if (user.getLevel() > 1)
			return (false);
	}
	else
	{
			user.setNickname(cmd[1]);
			user.addLevel();		
	}
	return (true);
}

bool Server::nick(std::string nickname, int fd)
{
	User &user = GetUserByFd(fd);
	std::string toUpdate;
	std::string secondChoice = user.getSecondChoice();
	
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
			if (secondChoice.empty())
				user.setSecondChoice(nickname);
			return (false);
		}
	}
	if (secondChoice.empty())
		toUpdate = nickname;
	else
		toUpdate = secondChoice;
 	user.setSecondChoice(nickname);
	user.setNickname(toUpdate);
	std::map<int, User>::iterator start = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); start != it; ++it)
	{
		sendStringSocket(it->second.getFd(), RPL_NICK(toUpdate, user.getUsername(), nickname));
	} 
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

std::string Server::getNickname(std::string msg)
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