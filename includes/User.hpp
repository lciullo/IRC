#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
		std::string					_nickname;
		std::string					_username;
		std::string					_oldNickname;
		int 						_fd;
		int							_level;
		std::string					_line;
		std::vector<std::string>	_userChannels;
		std::vector<std::string>	_invite;
		
	public :

		//Constructor
		User(void);
		User(int fd);
  
		//Getters
		std::string					getNickname(void) const;
		std::string					getUsername(void) const;
		std::string					getoldNickname(void) const;
		const int &					getFd(void) const;
		int 						getLevel(void) const;
		std::string					getLine(void) const;
		std::vector<std::string> &	getUserChannels(void);
		std::vector<std::string>	getInvite(void) const;

		//Setters
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setoldNickname(std::string oldNickname);
		void setLine(std::string line);
				
		//Add
		void addLevel();
		void addChannel(std::string name_channel);
		void addInvite(std::string channel_name);

		//Delete
		void deleteChannel(std::string name_channel);
		void deleteInvite(std::string channel_name);
};

#endif