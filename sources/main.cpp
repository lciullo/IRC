#include "IRC.hpp"

#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << RED << "[ERROR] Wrong number of arguments" << RESET << std::endl;
		std::cout << GREEN << "Usage : ./ircserv <port> <password>" << RESET << std::endl;
		return (1);
	}
	Server srv(atoi(av[1]), av[2]);
	srv.launch();
}