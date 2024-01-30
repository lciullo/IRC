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
		int 				_socketfd;
		struct sockaddr_in	_serv_addr;
		unsigned long		_address;
		int					_port;
		std::string			_password;
		std::vector<struct pollfd>		_lst_fd;
		std::map<int, User>				_lst_usr;
		std::map<std::string, Channel>	_lst_channel;
		void invite(std::string msg, int fd);
		void kick(std::string msg, int fd);
		bool isRightPassword(std::string msg, int fd);
		void join(std::string msg, int fd);
		void privmsg(std::string msg, int fd);
		void part(std::string msg, int fd);
		void quit(std::string msg, int fd);
		//utils to quit 
		bool searchChannelInServer(std::string target);
		void closeUserFd(int fd);
		void deleteUserFromChannel(User user);
		void deleteUserFromLst(int fd);
	public : 
		Server(int port, std::string _password);
		void launch();
		void add_user(int index, std::string nickname, std::string username);
		void create_user();
		void launch_cmd(std::string msg, int index);
		std::string getNickname(std::string msg);
		std::string getUsername(std::string msg);
		std::vector<struct pollfd> getLstFd() const;
		std::map<int, User> getLstUsr(void);
		//time_t*							getTime();
		User &GetUserByFd(int fd);
		User &GetUserByNickname(std::string nickname);
};

void sendUserList(Channel channel);
void getcmd(std::string str, std::string &cmd);

#endif