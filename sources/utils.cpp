#include "IRC.hpp"
#include "User.hpp"

void sendStringSocket(int socket, const std::string& str)
{
	std::cout << YELLOW << str << RESET;
	ssize_t bytesSent = send(socket, str.c_str(), str.length(), MSG_NOSIGNAL | MSG_DONTWAIT);
	if (bytesSent == -1)
		std::cerr << "Error sending data to client" << std::endl;
	return ;
}

void getcmd(std::string str, std::string &cmd)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\r' && str[i + 1] && str[i + 1] == '\n')
		{
			cmd = str.substr(0,i + 2);
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
}

bool	isMode(char mode) {
	if (mode == 'i' || mode == 't' || mode == 'k' || mode == 'o' || mode == 'l')
		return (true);
	return (false);
}

void	send_msg(User user, std::string msg)
{
	size_t byteSent = 0;

	while (byteSent < msg.length())
	{
		std::cout << YELLOW << msg << RESET;
		long len = send(user.getFd(), msg.c_str(), msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
		if (len < 0)
			break ;
		byteSent += len;
	}
}

void	split_cmd(std::vector<std::string> *cmd, std::string msg)
{
	size_t	begin;
	size_t	end;
	std::string	str;
	std::string	whitespace = " \t\n\r\f\v";
	size_t	last_non_space = 0;

	while (msg.size() != 0)
	{
		if (msg.find_first_not_of(whitespace) == std::string::npos)
			break ;

		begin = msg.find_first_not_of(whitespace);
		if (msg[begin] == ':') {
			end = msg.size();
		}
		else {
			end = msg.find(" ", begin);
		}

		str = msg.substr(begin, end);
		if ((last_non_space = str.find_last_not_of(whitespace)) != std::string::npos)
			str = str.substr(0, last_non_space + 1);

		cmd->push_back(str.c_str());
		msg.erase(0, end);
	}
}

void	print_vector(std::vector<std::string> cmd)
{
	std::vector<std::string>::iterator	it;
	for (it = cmd.begin(); it != cmd.end(); it++) {
		std::cout << *it << "|" << std::endl;
	}
}