#include "IRC.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>

int main(int ac, char **av)
{
	cout << MAGENTA << "On compile" << RESET << endl;
	int sockfd, newsockfd, port_no, n;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	// (void) n;
	// (void) newsockfd;
	// (void) cli_addr;
	if (ac < 2)
	{
		std::cout << "[ERROR] Not enough arguments";
		return (1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cout << "[ERROR] Creation of socket failed";
		return (1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	port_no = atoi(av[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
	{
		std::cout << "[ERROR] Bind socket failed";
		return (1);
	}
	std::vector<struct pollfd> lst_fd;
	struct pollfd first;
	first.fd = sockfd;
	first.events = POLLIN;
	lst_fd.push_back(first);
	listen(sockfd,5);
	clilen = sizeof(struct sockaddr_in);
	while (1)
	{
		if (poll(&lst_fd[0], lst_fd.size(), -1) >= 0)
		{
			if (lst_fd[0].revents & POLLIN)
			{
				std::cout << "NEW USER" << std::endl; 
				newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
				struct pollfd new_socket_fd;
				new_socket_fd.fd = newsockfd;
				new_socket_fd.events = POLLIN;
				lst_fd.push_back(new_socket_fd);
			}
			for (int i=1; i < (int)lst_fd.size(); i++) 
			{
				if (lst_fd[i].revents & POLLIN) {
					bzero(buffer,256);
					n = read(lst_fd[i].fd,buffer,255);
					std::string str(buffer);
					if (str.find("QUIT") != std::string::npos)
						lst_fd.erase(lst_fd.begin()+i);
					if (str.find("JOIN") != std::string::npos)
					{
						std::string message = ":ajakubcz!ajakubcz@localhost JOIN coucou\n";
						send(lst_fd[i].fd, message.c_str(), message.size(), 0);

					}
					std::cout << "[LOG] " << i <<  " : " << buffer << std::endl;
					// n = write(lst_fd[i].fd, ":Coucou\n", strlen(":Coucou\n") + 1);
					// std::string message = "test";
    				if (n < 0) 
						std::cout << "ERROR writing to socket" << std::endl;
				}
			}
		}
	}
	// close(newsockfd);
	close(sockfd);
	return 0;
}