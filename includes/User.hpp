#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
				std::string	_nickname;
				std::string	_channel; // pourquoi? plutot un vector non?
				std::string	_username;
				int 		_fd;
				bool		_isCreate;
				int			_level;
				User(void);

	public :
				//User(const std::string& nickname, const std::string& username, int fd, bool isCreate);
				User(int fd);
				~User(void);
				User &	operator=(const User &obj);

				const std::string& getNickname(void) const;
				const std::string& getUsername(void) const;
				const std::string& getChannel(void) const;
				const int& getFd(void) const;
				const bool& getIsCreate(void) const;
				void setIsCreate(bool isCreate);
				void setNickname(std::string nickname);
				void setUsername(std::string username);
				void addLevel();

				bool operator<(const User& other) const {
        			return this->getNickname() < other.getNickname();
   				 }

};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif