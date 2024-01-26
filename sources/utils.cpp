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