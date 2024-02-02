#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
		//Attributes
		std::string					_nickname;
		std::string					_username;
		std::vector<std::string>	_userChannels;
		int 						_fd;
		bool						_isCreate;
		int							_level;
		std::string					_secondChoice;

	public :
		//Constructor / destructors
		User(void);
		User(int fd);
		~User(void);
		User &	operator=(const User &obj);
				
		//Getters
		const std::string& getNickname(void) const;
		const std::string& getUsername(void) const;
		int getLevel(void) const;
		std::vector<std::string> &getUserChannels(void);
		const int& getFd(void) const;
		const bool& getIsCreate(void) const;
		std::string getSecondChoice(void);
				
		//Setters
		void setIsCreate(bool isCreate);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setSecondChoice(std::string SecondChoice);
		void addLevel();
				
		//Channel
		void addChannel(std::string name_channel);
		void deleteChannel(std::string name_channel);
		bool operator<(const User& other) const {
        	return this->getNickname() < other.getNickname();
   		}
};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif