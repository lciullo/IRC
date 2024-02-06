#include "Server.hpp"

bool Server::switchUserCase(User &user, std::string msg)
{
	std::vector<std::string> cmd;
	split_cmd(&cmd, msg);
	if (user.getLevel() == 0)
	{
		ERR_NOTREGISTERED(user);
		return (false);
	}
	if (cmd.size() != 5)
	{
		ERR_NEEDMOREPARAMS(user, "USER");
		return (false);
	}
	if (user.getUsername().empty() && user.getLevel() >= 1)
		user.addLevel();
	user.setUsername(findUsername(cmd[1]));
	return (true);
}


std::string Server::findUsername(std::string msg)
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