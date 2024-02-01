
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
	int 			n;
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
			for (int i=1; i < (int)this->_lst_fd.size(); i++)
			{
				if (this->_lst_fd[i].revents & POLLIN){
					bzero(buffer,256);
					n = read(this->_lst_fd[i].fd,buffer,255);
					if (n < 0)
						std::cout << "ERROR writing to socket" << std::endl;
					std::string str(buffer);
					std::string cmd = "";
					getcmd(str, cmd);
					while (cmd.size() != 0)
					{
						std::cout << "[LOG] " << i << " " << cmd << "|" << std::endl;
						str = str.substr(cmd.size() + 2);
						this->launch_cmd(cmd, this->_lst_fd[i].fd);
						getcmd(str, cmd);
					}
				}
				// if regarder l'event deconnection quand on a pas de quit on envoie un quit man poll HR2
			}
		}
	}
}

/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void Server::launch_cmd(std::string msg, int fd)
{
	User &user = GetUserByFd(fd);
	if (msg.find("PASS") != std::string::npos)
	{
		if (isRightPassword(msg, fd) == true)
			user.addLevel();
	} 
	else if (msg.find("NICK") != std::string::npos)
	{
		if (nick(getNickname(msg), fd) == false)
		{
			if (user.getLevel() == 1)
				closeUserFd(fd);
			if (user.getLevel() > 1)
				return ;
		}
		else
		{
			user.setNickname(getNickname(msg));
			user.addLevel();
		}

	}
	else if (msg.find("USER") != std::string::npos)
	{
		user.setUsername(getUsername(msg));	
		user.addLevel();
	}
	else if (msg.find("JOIN") != std::string::npos)
		this->join(msg, fd);
	else if (msg.find("PART") != std::string::npos)
		this->part(msg, fd);
	else if (msg.find("PRIVMSG") != std::string::npos)
		this->privmsg(msg, fd);
	else if (msg.find("INVITE") != std::string::npos)
		this->invite(msg, fd);
	else if (msg.find("KICK") != std::string::npos)
		this->kick(msg, fd);
	else if (msg.find("TOPIC") != std::string::npos)
		this->topic(msg, fd);
	else if (msg.find("QUIT") != std::string::npos)
		this->quit(msg, fd);
	else if (msg.find("MODE") != std::string::npos)
		this->mode(msg, fd);
}


void Server::create_user()
{
	struct sockaddr_in cli_addr;
	socklen_t clilen;

	std::cout << "Create User : " << std::endl;
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


std::vector<struct pollfd> Server::getLstFd() const {return (this->_lst_fd);}

std::map<int, User> Server::getLstUsr(void)
{
	return (this->_lst_usr);
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
