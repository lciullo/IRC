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
		std::map<std::string,Channel> _lst_channel; //std::string == non du channel
		void invite(std::string msg, int index);
		void kick(std::string msg, int index);
		void mode(std::string msg, int index);
		bool isRightPassword(std::string msg, int index);
		void join(std::string msg, int index);
		void privmsg(std::string msg, int index);
		void part(std::string msg, int index);
	public : 
		Server(int port, std::string _password);
		void launch();
		void add_user(int index, std::string nickname, std::string username);
		void create_user();
		void launch_cmd(std::string msg, int index, int *level, std::string nickname, std::string username);
		void launch_cmd(std::string msg, int index, int *level);
		std::string getNickname(std::string msg);
		std::string getUsername(std::string msg);
		std::vector<struct pollfd> getLstFd() const;
		User &GetUserByFd(int fd);
		User &GetUserByNickname(std::string nickname);
};

void sendUserList(Channel channel);

#endif