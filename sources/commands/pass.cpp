#include "Server.hpp"

bool Server::switchPassCase(User &user, std::string msg, int fd)
{
	if (user.getLevel() >= 1)
	{
		ERR_ALREADYREGISTERED(user);
		return (false);
	}
	if (isRightPassword(user, msg, fd) == true)
	{
		if (user.getLevel() == 0)
		{
			user.addLevel();
			return (true);
		}
	}
	return (true);
}

bool Server::isRightPassword(User &user,std::string msg, int fd)
{
	std::istringstream	iss(msg);
	
	std::vector<std::string> cmd;
	std::string			line;
	std::string			password;
	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "PASS");
		return (false);
	}
	while (std::getline(iss, line)) 
	{
		size_t pos = line.find("PASS");
		if (pos != std::string::npos) {
			password = line.substr(5);
			password = password.substr(0, password.size());
		}
	}
	if (password != this->_password)
	{
		ERR_PASSWDMISMATCH(GetUserByFd(fd));
		close(fd);
		for (size_t i = 0; i < this->_lst_fd.size(); i++)
		{
			if (this->_lst_fd[i].fd == fd) {
				this->_lst_fd.erase(this->_lst_fd.begin() + i);
				break;
			}
		}
		return (false);
	}
	return (true);
}