#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
				std::string	_nickname;
				std::string	_channel;
				std::string	_username;
				int 		_fd;
				User(void);

	public :
				User(const std::string& nickname, const std::string& username, int fd);
				~User(void);
				const std::string& getNickname(void) const;
				const std::string& getUsername(void) const;
				const int& getFd(void) const; 
};

#endif