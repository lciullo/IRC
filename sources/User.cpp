
#include "User.hpp"


User::User(void){

}

User::User(const std::string& nickname, const std::string& username, int fd): _nickname(nickname), _username(username), _fd(fd) {
	return ;
}

User::~User(void) {
	return;
}

const std::string& User::getNickname(void) const 
{
		return (_nickname);
}


const std::string& User::getUsername(void) const 
{
	return (_username);
}

const int& User::getFd(void) const
{
	return (_fd);
}