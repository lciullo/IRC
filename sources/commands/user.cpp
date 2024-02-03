#include "Server.hpp"

std::string Server::getUsername(std::string msg)
{
	size_t				end = 0;
	std::istringstream	iss(msg);
	std::string			line;
	std::string			username;
	while (std::getline(iss, line)) 
	{
		size_t index = line.find("USER");
		if (index != std::string::npos) 
		{
			for (size_t i = 5; i < line.size(); i++){
				if (line[i] == ' ')
				{
					end = i;
					break ;
				}
			}
			username = line.substr(5,end - 5);
		}
	}
	return (username);
}