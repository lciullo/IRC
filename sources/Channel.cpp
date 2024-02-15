/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:47:41 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/14 15:55:11 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default") {
	this->_private = false;
	this->_nbrUser = 0;
	this->_nbrUserMax = -1;
}

Channel::Channel(std::string name, User *operators) {
	this->_nbrUser = 1;
	this->_nbrUserMax = -1;
	this->_private = false;
	this->_name = name; 
	this->_vecUsers.push_back(operators);
	this->_lstUsers[operators] = OPERATOR;
	operators->addChannel(this->_name);
}

Channel::Channel(const Channel &channel)
{
	this->_nbrUser = channel._nbrUser;
	this->_nbrUserMax = channel._nbrUserMax;
	this->_private = channel._private;
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_password = channel._password;
	this->_topicInfo = channel._topicInfo;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_vecUsers = channel._vecUsers;
	this->_lstUsers = channel._lstUsers;
}

Channel &Channel::operator=(const Channel &channel)
{
	this->_nbrUser = channel._nbrUser;
	this->_nbrUserMax = channel._nbrUserMax;
	this->_private = channel._private;
	this->_name = channel._name;
	this->_topic = channel._topic;
	this->_password = channel._password;
	this->_topicInfo = channel._topicInfo;
	this->_mode = channel._mode;
	this->_waitlist = channel._waitlist;
	this->_vecUsers = channel._vecUsers;
	this->_lstUsers = channel._lstUsers;
	return (*this);
}

/*- - - - - - - - - - - - - - - - - GETTERS  - - - - - - - - - - - -- - - - - */
int			Channel::getNbrUser() const {return (this->_nbrUser);}

int			Channel::getNbrUserMax() const {return (this->_nbrUserMax);}

bool		Channel::getStatus() const {return (this->_private);}

std::string	Channel::getName() const {return (this->_name);}

std::string	Channel::getTopic() const {return (this->_topic);}

std::string	Channel::getPassword() const {return (this->_password);}


std::string	Channel::getTopicInfo() const {return (this->_topicInfo);}

std::string	Channel::getModestring() const {
	std::string	modestring;
	
	std::vector<char>::const_iterator	it;
	for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
		modestring += *it;
	}
	return (modestring);
}

std::vector<User *>		Channel::getVecUsers() const {return (this->_vecUsers);}

std::vector<User *>		Channel::getwaitlist() const {return (this->_waitlist);}

std::map<User *, int>	Channel::getLstUsers() const {return (this->_lstUsers);}

/*- - - - - - - - - - - - - - - - - SETTERS - - - - - - - - - - - -- - -  - - */

void	Channel::setTopic(std::string topic, std::string nickSetter) {

	this->_topicInfo = nickSetter;
	if (topic.empty()) {
		this->_topic.clear();
		return ;
	}
	this->_topic = topic;
}

/*- - - - - - - - - - - - - - - - - - ADD - - - - - - - - - - - - - -- - - - -*/
void	Channel::addUser(User *new_user)
{
	this->_vecUsers.push_back(new_user);
	this->_lstUsers[new_user] = VOICE;
	this->_nbrUser += 1;
	new_user->addChannel(this->_name);
}

bool	Channel::addMode(char new_mode, std::string param)
{
	switch (new_mode) {
		case 'i' : {
			this->_private = true;
			break ;
		}
		case 'k' : {this->_password = param;
			break;
		}
		case 'l' : {
			this->_nbrUserMax = atoi(param.c_str());
			break;
		}
		case 'o' : {
			std::map<User *, int>::iterator	it;
			for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
				if (it->first->getNickname() == param) {
					it->second = OPERATOR;
					return (true);
				}
			}
			return (false);
		}
	}
	
	this->_mode.push_back(new_mode);
	return (true);
}

void	Channel::addUserToWaitlist(User *guest)
{
	this->_waitlist.push_back(guest);
}

/*- - - - - - - - - - - - - - - - - -DELETE  - - - - - - - - - - -- - - - - - */
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

bool	Channel::deleteMode(char mode, std::string param)
{	
	std::vector<char>::iterator	it;
	if (mode == 'o') {
		std::map<User *, int>::iterator	it;
		for (it = _lstUsers.begin(); it != _lstUsers.end(); it++) {
			if (it->first->getNickname() == param) {
				it->second = VOICE;
				return (true) ;
			}
		}
		return (false);
	}
	for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
		if (*it == mode) {
			this->_mode.erase(it);
			switch (mode) {
				case 'i' : {
					this->_private = false;
					break ;
				}
				case 'k' : {
					this->_password.clear();
					break;
				}
				case 'l' : {
					this->_nbrUserMax = -1;
					break;
				}
			}
			break;
		}
	}
	return (true);
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

/*- - - - - - - - - - - - - - - - -  FIND  - - - - - - - - - - - - -- - - - - */
bool	Channel::findUser(User *user) const {
	
	std::map<User *, int>::const_iterator	it;
	
	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user->getNickname() == it->first->getNickname())
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
