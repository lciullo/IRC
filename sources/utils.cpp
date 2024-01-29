#include "IRC.hpp"


void getcmd(std::string str, std::string &cmd)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\r' && str[i + 1] && str[i + 1] == '\n')
		{
			cmd = str.substr(0,i);
			return ;
		}
		i++;
	}
	cmd = "";

}

void	split_arg(std::vector<std::string> *cmd, std::string arg)
{
	size_t end;
	std::string	str;

	while (arg.size() != 0)
	{
		end = arg.find(',');
		if (end == std::string::npos)
		{
			end = arg.size();
			str = arg.substr(0, end);
			arg.erase(0, end);
		}
		else
		{
			str = arg.substr(0, end);
			arg.erase(0, end + 1);
		}
		cmd->push_back(str);
	}
	std::cout << std::endl;
}