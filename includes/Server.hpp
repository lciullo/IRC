#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "Numerics.hpp"
#include <map>


//======== DEFINE FOR CMD ==========//

# define HEADER_CMD(User) \
":" + User.findNickname() + "!" + User.findUsername() + " "

class User;

class Server
{
	private :
		
		//Attributes
		int 				_socketfd;
		struct sockaddr_in	_serv_addr;
		unsigned long		_address;
		int					_port;
		std::string			_password;
		std::vector<struct pollfd>		_lst_fd;
		std::map<int, User>				_lst_usr;
		std::map<std::string, Channel>	_lst_channel;
		
		//Commands
		void invite(std::string msg, int fd);
		void kick(std::string msg, int fd);
		void mode(std::string msg, int fd);
		void topic(std::string msg, int fd);
		bool isRightPassword(std::string msg, int fd);
		void join(std::string msg, int fd);
		void privmsg(std::string msg, int fd);
		void part(std::string msg, int fd);
		void quit(std::string msg, int fd);
		
		//========== NICK ==========
		bool nick(std::string nickname, int fd);
		bool switchNickCase(std::string msg, int fd);
		bool isValidNickname(std::string nickname);
		void sendNewNickname(User &user, std::string toUpdate, std::string nickname);
		void sendInEachChannel(Channel &channel, User &user, std::string toUpdate, std::string nickname);
		//Delete 
		bool searchChannelInServer(std::string target);
		void closeUserFd(int fd);
		void deleteUserFromChannel(User user);
		void deleteUserFromLst(int fd);
		
	public : 
		//Constructor 
		Server(int port, std::string _password);
		
		//Commands
		void launch();
		void launch_cmd(std::string msg, int index);
		std::string findNickname(std::string msg);
		std::string findUsername(std::string msg);
		//User
		void add_user(int index, std::string nickname, std::string username);
		void create_user();
		
		//Getters
		
		std::string getNickname(void);
		std::string getUsername(void);
		std::string getPassword(void);
		std::vector<struct pollfd> getLstFd() const;
		std::map<int, User> getLstUsr(void);
		User &GetUserByFd(int fd);
		User &GetUserByNickname(std::string nickname);
		bool searchUserInServer(std::string nickname);
};

void sendUserList(Channel channel);
void getcmd(std::string str, std::string &cmd);
void split_arg(std::vector<std::string> *cmd, std::string arg);

#endif