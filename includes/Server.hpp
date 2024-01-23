#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <map>
class User;

class Server
{
	private :
		int _socketfd;
		struct sockaddr_in _serv_addr;
		unsigned long _address;
		int _port;
		std::string _password;
		std::vector<struct pollfd> _lst_fd;
		std::vector<User> _lst_usr;
		std::map<std::string,Channel> _lst_channel;
		void invite(std::string msg, int index);

	public : 
		Server(int port, std::string _password);
		void launch();
		void add_user(std::string msg);
		void create_user();
		void launch_cmd(std::string msg, int index);
		//COMMAND
		void join(std::string msg, int index);
		void privmsg(std::string msg, int index);
};

#endif