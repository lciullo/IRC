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
				bool		_isCreate;
				User(void);

	public :
				User(const std::string& nickname, const std::string& username, int fd, bool isCreate);
				~User(void);
				const std::string& getNickname(void) const;
				const std::string& getUsername(void) const;
				const std::string& getChannel(void) const;
				const int& getFd(void) const;
				const bool& getIsCreate(void) const;
				void setIsCreate(bool isCreate); 
				bool operator<(const User& other) const {
        			return this->getNickname() < other.getNickname();
   				 }

};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif