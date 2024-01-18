#include "IRC.hpp"
#include "Server.hpp"
#include <cstdlib>

bool good_arg(char *port, char *address);

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << RED << "[ERROR] Wrong number of arguments" << RESET << std::endl;
		std::cout << GREEN << "Usage : ./ircserv <port> <password>" << RESET << std::endl;
		return (1);
	}
	if (!good_arg(av[1], av[2]))
	{
		return (1);
	}
	Server srv(atoi(av[1]), av[2]);
	srv.launch();
}

bool good_arg(char *port, char *address)
{
	(void) address;
	int port_nbr;

	for (int i = 0; port[i]; i++)
	{
		if (port[i] < '0' || port[i] > '9')
		{
			std::cout << RED << "[ERROR] Wrong port : \"" << port << "\", put only digit in port" << RESET << std::endl;
			return false;
		}
	}
	port_nbr = atoi(port);
	if (port_nbr < 1024 || port_nbr > 65535)
	{
		std::cout << RED << "[ERROR] Wrong port : \"" << port << "\", put port between 1024 and 65535" << RESET << std::endl;
		return false;
	}
	return true;
}