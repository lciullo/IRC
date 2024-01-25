#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <map>


//======== DEFINE FOR CMD ==========//
# define HEADER_CMD(User) \
":" + User.getNickname() + "!" + User.getUsername() + " "

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
		void kick(std::string msg, int index);

	public : 
		Server(int port, std::string _password);
		void launch();
		void add_user(std::string msg, int index);
		void create_user();
		void launch_cmd(std::string msg, int index, int *level);
		//COMMAND
		std::string getNickname(std::string msg);
		std::string getUsername(std::string msg);
		void join(std::string msg, int index);
		void privmsg(std::string msg, int index);
		void part(std::string msg, int index);

		User &GetUserByFd(int fd);
		User &GetUserByNickname(std::string nickname);
		/*class ambiguousNickname : public std::exception
		{
			public :
						const char *	what() const throw() 
						{
							return ("Error, ambiguous nickname");
						}
		};*/

};

void sendUserList(Channel channel);

#endif