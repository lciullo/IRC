
#include "User.hpp"


User::User(void){

}

User::User(const std::string& nickname, const std::string& username): _nickname(nickname), _username(username) {
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