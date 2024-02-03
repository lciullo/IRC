#ifndef USER_HPP
#define USER_HPP

#include "IRC.hpp"

class User
{
	private :
<<<<<<< HEAD
				std::string	_nickname;
				std::string	_username;
				std::vector<std::string>	_userChannels;
				std::vector<std::string>	_invite;
				int 		_fd;
				bool		_isCreate;
				int			_level;

	public :
				User(void);
				User(int fd);
				~User(void);
				User &	operator=(const User &obj);
				const std::string& getNickname(void) const;
				const std::string& getUsername(void) const;
				int getLevel(void) const; 
				std::vector<std::string> &getUserChannels(void);
				std::vector<std::string> getInvite(void) const;
				void addChannel(std::string name_channel);
				const int& getFd(void) const;
				const bool& getIsCreate(void) const;
				void setIsCreate(bool isCreate);
				void setNickname(std::string nickname);
				void setUsername(std::string username);
				void addLevel();
				void addInvite(std::string channel_name);
				void deleteChannel(std::string name_channel);
				void deleteInvite(std::string channel_name);
=======
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
>>>>>>> 25bc14a35f87c91d9a4cfd13f920251e42668c0b
				
		//Channel
		void addChannel(std::string name_channel);
		void deleteChannel(std::string name_channel);
		bool operator<(const User& other) const {
        	return this->getNickname() < other.getNickname();
   		}
};

std::ostream &operator<<(std::ostream &out, const User &Object);

#endif