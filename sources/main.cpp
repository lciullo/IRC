#include "IRC.hpp"

#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "[ERROR] Not good number of arguments";
		return (1);
	}
	Server srv(atoi(av[1]), av[2]);
	srv.launch();
}