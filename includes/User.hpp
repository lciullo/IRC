#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
				std::string	_nickname;
				std::string	_username;
				std::vector<std::string>	_userChannels;
				std::vector<std::string>	_invite;
				int 		_fd;
				bool		_isCreate;
				int			_level;

	public :
				User(void);
				User(int fd);
				~User(void);
				User &	operator=(const User &obj);
				const std::string& getNickname(void) const;
				const std::string& getUsername(void) const;
				int getLevel(void) const; 
				std::vector<std::string> &getUserChannels(void);
				std::vector<std::string> getInvite(void) const;
				void addChannel(std::string name_channel);
				const int& getFd(void) const;
				const bool& getIsCreate(void) const;
				void setIsCreate(bool isCreate);
				void setNickname(std::string nickname);
				void setUsername(std::string username);
				void addLevel();
				void addInvite(std::string channel_name);
				void deleteChannel(std::string name_channel);
				void deleteInvite(std::string channel_name);
				
				bool operator<(const User& other) const {
        			return this->getNickname() < other.getNickname();
   				}
};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif