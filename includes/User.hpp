#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
		//Attributes
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		std::string					_line;
		std::string					_oldNickname;
		std::vector<std::string>	_userChannels;
		std::vector<std::string>	_invite;
		int 						_fd;
		bool						_isCreate;
		int							_level;
		
	public :

		//Constructor / destructors
		User(void);
		User(int fd);
		~User(void);
		User &	operator=(const User &obj);
  
		//Getters
		const std::string& findNickname(void) const;
		const std::string& findUsername(void) const;
		int getLevel(void) const;
		std::vector<std::string> &getUserChannels(void);
		const int& getFd(void) const;
		const bool& getIsCreate(void) const;
		std::string getLine(void) const;
		std::string getoldNickname(void);
		std::string getNickname(void);
		std::string getUsername(void);
		//Setters
		void setIsCreate(bool isCreate);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setLine(std::string line);
		void setoldNickname(std::string oldNickname);
		void addLevel();
				
		//Channel
		void addChannel(std::string name_channel);
		void deleteChannel(std::string name_channel);
		bool operator<(const User& other) const {
        	return this->findNickname() < other.findNickname();
   		}

		void addInvite(std::string channel_name);
		void deleteInvite(std::string channel_name);
		std::vector<std::string> getInvite(void) const;
};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif