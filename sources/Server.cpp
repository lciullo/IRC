
#include "Server.hpp"
class User;


Server::Server(int port, std::string password)
{
	this->_address = INADDR_ANY;
	this->_port = port;
	this->_password = password;
	bzero((char *) &this->_serv_addr, sizeof(this->_serv_addr));
	this->_serv_addr.sin_family = AF_INET;
	this->_serv_addr.sin_port = htons(port);
	this->_serv_addr.sin_addr.s_addr = INADDR_ANY;
}

void Server::launch()
{
	char 			buffer[256];
	ssize_t 		n;
	int 			opt = 1;

	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
		exit(EXIT_FAILURE);
	if (this->_socketfd < 0) // coucou la zone c'est leon le bg je vous aimes
	{
		std::cout << "[ERROR] Creation of socket failed";
		return;
	}
	if (bind(this->_socketfd, (struct sockaddr *) &this->_serv_addr, sizeof(this->_serv_addr)))
	{
		std::cout << "[ERROR] Bind socket failed";
		return;
	}
	struct pollfd first;
	first.fd = this->_socketfd;
	first.events = POLLIN;
	this->_lst_fd.push_back(first);
	listen(this->_socketfd,5);
	while (1)
	{
		if (poll(&this->_lst_fd[0], this->_lst_fd.size(), -1) >= 0)
		{
			if (this->_lst_fd[0].revents & POLLIN)
			{
				std::cout << "NEW USER" << std::endl;
				this->create_user();
			}
			for (size_t i=1; i < this->_lst_fd.size(); i++)
			{
				if (this->_lst_fd[i].revents & POLLIN){
					bzero(buffer,256);
					n = recv(this->_lst_fd[i].fd,buffer,255,0);
					if (n < 0)
						std::cout << "ERROR writing to socket" << std::endl;
					if (n == 0)
					{
						this->quit("QUIT :test", this->_lst_fd[i].fd);
						continue ;
					}
					User &user = GetUserByFd(this->_lst_fd[i].fd);
					user.setLine(user.getLine().append(buffer));
					std::string cmd = "";
					getcmd(user.getLine(), cmd);
					while (cmd.size() != 0)
					{
						// std::cout << "[LOG] " << i << " " << cmd << "|" << std::endl;
						user.setLine(user.getLine().substr(cmd.size() + 2));
						std::string str = user.getLine();
						this->launch_cmd(cmd, this->_lst_fd[i].fd);
						getcmd(str, cmd);
					}
				}
			}
		}
	}
}

/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void Server::launch_cmd(std::string msg, int fd)
{
	User &user = GetUserByFd(fd);
	std::vector<std::string> cmd;
	split_cmd(&cmd, msg);
	if (cmd.size() < 1)
		return ;
	if (cmd[0] == "QUIT")
	{
		this->quit(msg, fd);
		std::cout << "quit " << std::endl;
	}
	else if (cmd[0] == "PASS")
	{
		if (switchPassCase(user, msg, fd)== false)
			return ;
	} 
	else if (cmd[0] == "NICK")
	{
		if (switchNickCase(user, msg,fd) == false)
			return ;
	}
	else if (cmd[0] == "USER")
	{
		if (switchUserCase(user, msg) == false)
			return ;
	}
	else if (user.getLevel() < 2)
	{
		ERR_NOTREGISTERED(user);
		return ;
	}
	else if (cmd[0] == "JOIN")
		this->join(msg, fd);
	else if (cmd[0] == "PART")
		this->part(msg, fd);
	else if (cmd[0] == "PRIVMSG")
		this->privmsg(msg, fd);
	else if (cmd[0] == "INVITE")
		this->invite(msg, fd);
	else if (cmd[0] == "KICK")
		this->kick(msg, fd);
	else if (cmd[0] == "TOPIC")
		this->topic(msg, fd);
	
	else if (cmd[0] == "MODE")
		this->mode(msg, fd);
}


void Server::create_user()
{
	struct sockaddr_in cli_addr;
	socklen_t clilen;

	clilen = sizeof(struct sockaddr_in);
	int newsockfd = accept(this->_socketfd, (struct sockaddr *) &cli_addr, &clilen);
	std::cout << "fd : " << newsockfd << std::endl;
	struct pollfd new_socket_fd;
	new_socket_fd.fd = newsockfd;
	new_socket_fd.events = POLLIN;
	new_socket_fd.revents = 0;
	User user(newsockfd);
	this->_lst_usr[newsockfd] = user;
	this->_lst_fd.push_back(new_socket_fd);
}


/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */


std::vector<struct pollfd> Server::getLstFd() const 
{
	return (this->_lst_fd);
}

std::map<int, User> Server::getLstUsr(void) const
{
	return (this->_lst_usr);
}

std::string Server::getPassword(void) const
{
	return (this->_password);
}

User &Server::GetUserByFd(int fd)
{
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getFd() == fd)
			return (it->second);
	}
	return (ite->second);
}

User &Server::GetUserByNickname(std::string nickname)
{
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getNickname() == nickname)
			return (it->second);
	}
	return (ite->second);
}

bool Server::searchUserInServer(std::string nickname)
{
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getNickname() == nickname)
			return (true);
	}
	return (false);
}