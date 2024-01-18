
#include "Server.hpp"

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
	char buffer[256];
	int n;

	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
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
					this->launch_cmd(str, i);
					std::cout << "[LOG] " << i <<  " : " << buffer << std::endl;
				}
			}
		}
	}
}

void Server::launch_cmd(std::string msg, int index)
{
	if (msg.find("NICK") != std::string::npos)
		this->add_user(msg);
	if (msg.find("QUIT") != std::string::npos)
		this->_lst_fd.erase(this->_lst_fd.begin() + index);
	// if (str.find("JOIN") != std::string::npos)
	// {
	// 	std::string message = ":ajakubcz!ajakubcz@localhost JOIN coucou\n";
	// 	send(this->_lst_fd[i].fd, message.c_str(), message.size(), 0);
	// }
}

void Server::create_user()
{
	struct sockaddr_in cli_addr;
	socklen_t clilen;

	std::cout << "Create User : " << std::endl;
	clilen = sizeof(struct sockaddr_in);
	int newsockfd = accept(this->_socketfd, (struct sockaddr *) &cli_addr, &clilen);
	struct pollfd new_socket_fd;
	new_socket_fd.fd = newsockfd;
	new_socket_fd.events = POLLIN;
	this->_lst_fd.push_back(new_socket_fd);
}

void Server::add_user(std::string msg)
{
	std::cout << "New User : " << msg << std::endl;
	
	//NEED TO PARSE msg
}