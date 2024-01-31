
#include "User.hpp"


User::User(void){

}

User::User(int fd) : _nickname("default"), _username("default"), _fd(fd), _isCreate(false), _level(0)
{
	return ;
}

User::~User(void) {
	return;
}

User &	User::operator=(const User &obj){
	this->_nickname = obj._nickname;
	this->_username = obj._username;
	this->_fd = obj._fd;
	this->_isCreate = obj._isCreate;

	return (*this);
}

const std::string& User::getNickname(void) const 
{
		return (this->_nickname);
}


const std::string& User::getUsername(void) const 
{
	return (this->_username);
}

const int& User::getFd(void) const
{
	return (this->_fd);
}

const bool& User::getIsCreate(void) const
{
	return (this->_isCreate);
}

std::vector<std::string> User::getUserChannels(void)
{
	return (this->_userChannels);
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

void User::addChannel(std::string name_channel)
{
	std::cout << "[TEST] name : " << name_channel << std::endl;
	this->_userChannels.push_back(name_channel);
	std::cout << "add channel function" << std::endl;
	std::cout << "SIZE = " << this->_userChannels.size();
}