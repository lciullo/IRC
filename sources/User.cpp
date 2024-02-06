
#include "User.hpp"
#include <algorithm>

User::User(void):  _level(0)
{

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

std::string User::getoldNickname(void)
{
	return (this->_oldNickname);
}

std::vector<std::string> &User::getUserChannels(void)
{
	return (this->_userChannels);
}

std::vector<std::string> User::getInvite(void) const
{
	return (this->_invite);
}

int User::getLevel(void) const
{
	return (this->_level);
}

std::string User::getLine(void) const
{
	return (this->_line);
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

void User::setLine(std::string line)
{
	this->_line = line;
	return ;
}

void User::addLevel()
{
	this->_level += 1;
}

void	User::addInvite(std::string channel_name) 
{
	this->_invite.push_back(channel_name);
}


void User::setoldNickname(std::string oldNickname)
{
	this->_oldNickname = oldNickname;
	return ;
}

std::ostream &operator<<(std::ostream &out, const User &Object) {

	out << Object.getNickname() << " " << Object.getUsername() << " " << Object.getIsCreate() << std::endl;
	return (out);
}

void User::addChannel(std::string name_channel)
{
	// std::cout << "[TEST] name : " << name_channel << std::endl;
	this->_userChannels.push_back(name_channel);
	// std::cout << "add channel function" << std::endl;
	// std::cout << "SIZE = " << this->_userChannels.size();
}

void User::deleteChannel(std::string name_channel)
{
	std::vector<std::string>::iterator ite = this->_userChannels.end();
	for (std::vector<std::string>::iterator it = this->_userChannels.begin(); it != ite; ++it)
	{
		if (*it == name_channel)
		{
			this->_userChannels.erase(it);
			return ;
		}
	}
}

void	User::deleteInvite(std::string channel_name)
{
	std::vector<std::string>::iterator	it;
	it = std::find(this->_invite.begin(), this->_invite.end(), channel_name);
	if (it != this->_invite.end())
		this->_invite.erase(it);
}