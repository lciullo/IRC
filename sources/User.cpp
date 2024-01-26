
#include "User.hpp"


User::User(void){

}

//User::User(const std::string& nickname, const std::string& username, int fd): _nickname(nickname), _username(username), _fd(fd), _isCreate(false)
//{
//	return ;
//}

User::User(int fd) : _nickname("default"), _username("default"), _fd(fd), _isCreate(false), _level(0)
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

const std::string& User::getChannel(void) const 
{
	return (_channel);
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

void User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
	return ;
}

void User::setUsername(std::string username)
{
	this->_username = username;
	return ;
}

void User::addLevel()
{
	this->_level += 1;
}

std::ostream &operator<<(std::ostream &out, const User &Object) {

	out << Object.getNickname() << " " << Object.getUsername() << " " << Object.getIsCreate() << std::endl;
	return (out);
}