#include "Server.hpp"

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
	//check if is already exit command comment parcourir la liste ?
	//change usernickname 
	//verifier 
	return (nickname);
}

/*for (std::map<int, User*>::iterator it = this->_users.begin(); it != this->_users.end(); ++it) 
	{
		if (it->second->getNickname() == command[1])
		{
			ERR_NICKNAMEINUSE(this->_users[fd], command[1]);
			return (false);
		}
	}

	// Change the user's nickname
	RPL_CMD(this->_users[fd], "NICK", command[1]);
	this->_users[fd]->setNickname(command[1]);

	// Send to all channels the new nickname of the user
	for (size_t i = 0; i < this->_users[fd]->getChannels().size(); i++)
		this->_users[fd]->getChannels()[i]->sendUsersList();

	if (!this->_users[fd]->getLogged())
		this->_users[fd]->newConnection();*/