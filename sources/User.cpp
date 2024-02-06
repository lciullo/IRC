
#include "User.hpp"
#include <algorithm>


/*============================== CONSTRUCTOR ================================*/
User::User(void):  _level(0) {}

User::User(int fd) :_fd(fd), _level(0) {}


/*================================= GETTERS =================================*/
std::string User::getNickname(void) const {return (this->_nickname);}

std::string User::getUsername(void) const {return (this->_username);}

std::string User::getoldNickname(void) const {return (this->_oldNickname);}

const int& User::getFd(void) const {return (this->_fd);}

int User::getLevel(void) const {return (this->_level);}

std::string User::getLine(void) const {return (this->_line);}

std::vector<std::string> &User::getUserChannels(void) {return (this->_userChannels);}

std::vector<std::string> User::getInvite(void) const {return (this->_invite);}


/*================================= SETTERS =================================*/
void User::setNickname(std::string nickname) {this->_nickname = nickname;}

void User::setUsername(std::string username) {this->_username = username;}

void User::setoldNickname(std::string oldNickname) {this->_oldNickname = oldNickname;}

void User::setLine(std::string line) {this->_line = line;}


/*=================================== ADD ===================================*/
void User::addLevel() {this->_level += 1;}

void	User::addInvite(std::string channel_name) {this->_invite.push_back(channel_name);}

void User::addChannel(std::string name_channel) {this->_userChannels.push_back(name_channel);}


/*================================== DELETE =================================*/
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
