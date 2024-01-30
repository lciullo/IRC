/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:47:41 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/30 15:30:48 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, User *operators) : _name(name) {
	this->_lstUsers[operators] = OPERATOR;
	this->_vecUsers.push_back(operators);
	this->_private = false;
	this->_nbrUser += 1;
	this->_nbrUserMax = -1;
}

Channel::Channel(const Channel &channel)
{
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_lstUsers = channel._lstUsers;
	this->_vecUsers = channel._vecUsers;
}

Channel &Channel::operator=(const Channel &channel)
{
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_lstUsers = channel._lstUsers;
	this->_vecUsers = channel._vecUsers;
	return (*this);
}

/*- - - - - - - - - - - - - - - - - GETTERS - - - - - - - - - - - -- - -  - - */
std::string	Channel::getName() const {return (this->_name);}

std::string	Channel::getTopic() const {return (this->_topic);}

std::map<User *, int>  Channel::getLstUsers() const {return (this->_lstUsers);}

std::vector<User *> Channel::getVecUsers() const {return (this->_vecUsers);}

bool	Channel::getStatus() const {return (this->_private);}

int		Channel::getNbrUser() const {return (this->_nbrUser);};
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
	//}
}

void	Channel::addChannelMode(char new_mode, std::string param)
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
	
	if (new_mode == 'i')
		this->_private = true;
	else if (new_mode == 'k' && param != "no param")
		this->_password = param;
	else if (new_mode == 'l' && param != "no param")
	{
		unsigned long i;
		for (i = 0; i < param.size(); i++) {
			if (!isdigit(param[i]))
				break ;
		}
		this->_nbrUserMax = atoi(param.c_str());
	}
	this->_mode.push_back(new_mode);
	std::vector<char>::iterator itv;
	for (itv = this->_mode.begin(); itv != this->_mode.end(); itv++)
		std::cout << *itv << std::endl;
}

void	Channel::addUserToWaitlist(User *guest)
{
	this->_waitlist.push_back(guest);
}

void	Channel::addOperatorMode(std::string user_name)
{
	if (user_name == "no param")
		return ;
	
	std::map<User *, int>::iterator	it;
	for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
		if (it->first->getNickname() == user_name)
		{
			it->second = OPERATOR;
			return ;
		}
	}
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

void	Channel::deleteChannelMode(char mode, std::string param)
{
	(void) param;

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
			if (mode == 'i')
				this->_private = false;
			else if (mode == 'k')
				this->_password.clear();
			else if (mode == 'l')
				this->_nbrUserMax = -1;
			break;
		}
	}
	std::vector<char>::iterator itv;
	for (itv = this->_mode.begin(); itv != this->_mode.end(); itv++)
		std::cout << *itv << std::endl;
}

void		Channel::deleteOperatorMode(std::string user_name)
{
	if (user_name == "no param")
		return ;
	
	std::map<User *, int>::iterator	it;
	for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
		if (it->first->getNickname() == user_name)
		{
			it->second = VOICE;
			return ;
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
