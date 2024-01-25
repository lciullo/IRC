
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
	std::string 	nickname;
	std::string 	username;
	int 			n;
	int 			opt = 1;
	int 			level = 0;

	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
		exit(EXIT_FAILURE);
	if (this->_socketfd < 0)
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
				if (this->_lst_fd[i].revents & POLLIN) {
					bzero(buffer,256);
					n = read(this->_lst_fd[i].fd,buffer,255);
					if (n < 0)
						std::cout << "ERROR writing to socket" << std::endl;
					std::string str(buffer);
					std::cout << "[LOG] " << i << " " << str << std::endl;
					this->launch_cmd(str, i, &level, nickname, username);
					if (level == 2)
						this->add_user(i, nickname, username);
				}
				// if regarder l'event deconnection quand on a pas de quit on envoie un quit 
			}
		}
	}
}


/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void Server::launch_cmd(std::string msg, int index, int *level, std::string nickname, std::string username)
{ 
	if (msg.find("PASS") != std::string::npos && *level == 0)
	{
		if (isRightPassword(msg, index) == true)
			*level += 1;
	} 
	else if (msg.find("NICK") != std::string::npos && *level == 1)
	{
		nickname = getNickname(msg);
		*level += 1;
	}
	else if (msg.find("USER") != std::string::npos && *level == 2)
	{
		username = getUsername(msg);	
		*level += 1;
	}
	else if (msg.find("QUIT") != std::string::npos) 
		this->_lst_fd.erase(this->_lst_fd.begin() + index);
	else if (msg.find("JOIN") != std::string::npos)
		this->join(msg, index);
	else if (msg.find("PART") != std::string::npos)
		this->part(msg, index);
	else if (msg.find("PRIVMSG") != std::string::npos)
		this->privmsg(msg, index);
	else if (msg.find("INVITE") != std::string::npos)
		this->invite(msg, index);
	else if (msg.find("KICK") != std::string::npos)
		this->kick(msg, index);
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
	this->_lst_fd.push_back(new_socket_fd);
}


/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void  Server::add_user(int index, std::string nickname, std::string username)
{
	User user(nickname, username, this->_lst_fd[index].fd, false);
	for (std::vector<User>::const_iterator it = _lst_usr.begin(); it != _lst_usr.end(); ++it) 
	{
		if (it->getNickname() == nickname && it->getIsCreate() == true)
		{
			std::cout << RED << "<client> <nick> :Nickname is already in use" << RESET << std::endl;
			return ;
		}
	std::cout << BLUE << *it << RESET;
		it->getNickname();
	}
   	this->_lst_usr.push_back(user);
	this->_lst_usr.back().setIsCreate(true);
	return ;
}

std::vector<struct pollfd> Server::getLstFd() const {return (this->_lst_fd);}

User &Server::GetUserByFd(int fd)
{
	std::vector<User>::iterator ite = this->_lst_usr.end();
	for (std::vector<User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->getFd() == fd)
			return (*it);
	}
	return (*ite);
}

User &Server::GetUserByNickname(std::string nickname)
{
	std::vector<User>::iterator ite = this->_lst_usr.end();
	for (std::vector<User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->getNickname() == nickname)
			return (*it);
	}
	return (*ite);
}

/*
creat une function lors de la deconnection du client qui va supprimer 
du vecteur user 
de la map channel 
std::map<User, int>	_lstUsers;
std::vector<User>	_vecUsers;
*/