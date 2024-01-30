#include "Server.hpp"

bool Server::isRightPassword(std::string msg, int fd)
{
	std::istringstream	iss(msg);
	std::string			line;
	std::string			password;
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
		const char* quitMessage = " <client> :Password incorrect";
   		send(fd, quitMessage, strlen(quitMessage), 0);
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