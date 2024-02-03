/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:47:41 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 13:43:08 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default") {
	this->_private = false;
	this->_nbrUser = 0;
	this->_nbrUserMax = -1;
}


Channel::Channel(std::string name, User *operators) : _name(name) {
	this->_lstUsers[operators] = OPERATOR;
	this->_vecUsers.push_back(operators);
	operators->addChannel(this->_name);
	this->_private = false;
	this->_nbrUser = 1;
	this->_nbrUserMax = -1;
}

Channel::Channel(const Channel &channel)
{
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_password = channel._password;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_lstUsers = channel._lstUsers;
	this->_vecUsers = channel._vecUsers;
	this->_nbrUser = channel._nbrUser;
	this->_nbrUserMax = channel._nbrUserMax;
	this->_private = channel._private;
}

Channel &Channel::operator=(const Channel &channel)
{
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_password = channel._password;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_lstUsers = channel._lstUsers;
	this->_vecUsers = channel._vecUsers;
	this->_nbrUser = channel._nbrUser;
	this->_nbrUserMax = channel._nbrUserMax;
	this->_private = channel._private;
	return (*this);
}

/*- - - - - - - - - - - - - - - - - GETTERS - - - - - - - - - - - -- - -  - - */
std::string	Channel::getName() const {return (this->_name);}

std::string	Channel::getTopic() const {return (this->_topic);}

std::map<User *, int>	Channel::getLstUsers() const {return (this->_lstUsers);}

std::vector<User *>	Channel::getVecUsers() const {return (this->_vecUsers);}

bool	Channel::getStatus() const {return (this->_private);}

int		Channel::getNbrUser() const {return (this->_nbrUser);};

int		Channel::getNbrUserMax() const {return (this->_nbrUserMax);};

std::string	Channel::getPassword() const {return (this->_password);}

/*- - - - - - - - - - - - - - - - - SETTERS - - - - - - - - - - - -- - -  - - */
void	Channel::setName(std::string name) {this->_name = name;}

void	Channel::setTopic(std::string topic) {this->_topic = topic;}

/*- - - - - - - - - - - - - - - - - - ADD - - - - - - - - - - - - -- - -  - -*/

void	Channel::addUser(User *new_user)
{
	//if (findUser(new_user) == false) {
		this->_vecUsers.push_back(new_user);
		this->_lstUsers[new_user] = VOICE;
		this->_nbrUser += 1;
		new_user->addChannel(this->_name);
}

void	Channel::addMode(char new_mode, std::string param)
{
	{
		std::vector<char>::iterator	it;
		for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
			if (*it == new_mode) {
				std::cout << "ERROR The mode ou are trying to add is already enable" << std::endl;
				return ;
			}
		}
	}
	
	switch (new_mode) {
		case 'i' : {this->_private = true;
			// std::cout << this->_private << std::endl;
			break ;
		}
		case 'k' : {this->_password = param;
			// if (!this->_password.empty())
				// std::cout << this->_password << std::endl;
			// else
				// std::cout << "Password is empty\n";
			break ;
		}
		case 'l' : {
			unsigned long i;
			for (i = 0; i < param.size(); i++) {
				if (!isdigit(param[i])) {
					std::cout << "The parameters must only be numbers\n";
					return ;
				}
			}
			this->_nbrUserMax = atoi(param.c_str());
			// std::cout << this->_nbrUserMax << std::endl;
			break ;
		}
		case 'o' : {
			std::map<User *, int>::iterator	it;
			for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
				if (it->first->getNickname() == param) {
					it->second = OPERATOR;
					break ;
				}
			}
			return ;
		}
	}
	
	this->_mode.push_back(new_mode);

	// std::vector<char>::iterator it2;
	// for (it2 = this->_mode.begin(); it2 != this->_mode.end(); it2++) {
		// std::cout << *it2 << " ";
	// }
	// std::cout << std::endl;
}

void	Channel::addUserToWaitlist(User *guest)
{
	this->_waitlist.push_back(guest);
}

/*- - - - - - - - - - - - - - - - - -DELETE - - - - - - - - - - -- - -  - - - */

void	Channel::deleteUser(User &user) 
{
	std::map<User *, int>::iterator	it_map;
	for (it_map = this->_lstUsers.begin(); it_map != this->_lstUsers.end(); it_map++) {
		if (user.getNickname() == it_map->first->getNickname()){
			this->_lstUsers.erase(it_map);
			break ;
		}
	}
	
	std::vector<User *>::iterator	it_vec;
	for (it_vec = this->_vecUsers.begin(); it_vec != this->_vecUsers.end(); it_vec++) {
		if (user.getNickname() == (*it_vec)->getNickname()) {
			this->_vecUsers.erase(it_vec);
			break ;
		}
	}
	this->_nbrUser -= 1;
}

void	Channel::deleteMode(char mode, std::string param)
{
	{
		std::vector<char>::iterator	it;
		for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
			if (*it == mode) {
				break ;
			}
		}
		
	}
	
	std::vector<char>::iterator	it;
	for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
		if (*it == mode) {
			this->_mode.erase(it);
			switch (mode) {
				case 'i' : {this->_private = false;
					// std::cout << this->_private << std::endl;
				}
				case 'k' : {this->_password.clear();
					// if (!this->_password.empty())
						// std::cout << this->_password << std::endl;
					// else
						// std::cout << "Password is empty\n";
				}
				case 'l' : {this->_nbrUserMax = -1;
					// std::cout << this->_nbrUserMax << std::endl;
				}
				case 'o' : {
					std::map<User *, int>::iterator	it;
					for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
						if (it->first->getNickname() == param) {
							it->second = VOICE;
							break ;
						}
					}
				}
			}
			break;
		}
	}

	// std::vector<char>::iterator it2;
	// for (it2 = this->_mode.begin(); it2 != this->_mode.end(); it2++) {
		// std::cout << *it2 << " ";
	// }
	// std::cout << std::endl;
}

void	Channel::deleteUserToWaitlist(User user) 
{	
	std::vector<User *>::iterator	it;
	for (it = this->_waitlist.begin(); it != this->_waitlist.end(); it++) {
		if (user.getNickname() == (*it)->getNickname())
		{
			this->_waitlist.erase(it);
			break ;
		}
	}
}

/*- - - - - - - - - - - - - - - - -  FIND - - - - - - - - - - - - -- - -  - - */
bool	Channel::findUser(User *user) const {
	
	std::map<User *, int>::const_iterator	it;
	
	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user->getNickname() == it->first->getNickname())
			return (true);
	}
	return (false);
}

bool	Channel::findOperators(User &user) const {
	
	std::map<User *, int>::const_iterator	it;
	
	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if ((user.getNickname() == it->first->getNickname()) && it->second == OPERATOR)
			return (true);
	}
	return (false);
}

bool	Channel::findInWaitList(User user) const
{
	std::vector<User *>::const_iterator	it;
	
	for (it = this->_waitlist.begin(); it != this->_waitlist.end(); it++) {
		if (user.getNickname() == (*it)->getNickname())
			return (true);
	}
	return (false);
}
