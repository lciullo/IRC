
#include "User.hpp"


User::User(void){

}

User::User(const std::string& nickname, const std::string& username, int fd, bool isCreate): _nickname(nickname), _username(username), _fd(fd), _isCreate(isCreate)
{
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

const bool& User::getIsCreate(void) const
{
	return (_isCreate);
}

void User::setIsCreate(bool isCreate)
{
	this->_isCreate = isCreate;
	return ;
}

std::ostream &operator<<(std::ostream &out, const User &Object) {

	out << Object.getNickname() << " " << Object.getUsername() << " " << Object.getIsCreate() << std::endl;
	return (out);
}