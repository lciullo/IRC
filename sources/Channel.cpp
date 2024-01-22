/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:47:41 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/22 14:56:38 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, User &operators) : _name(name) {
	this->_lstUsers[operators] = OPERATOR;
	this->_vecUsers.push_back(operators);
}

/*- - - - - - - - - - - - - - - - - GETTERS - - - - - - - - - - - -- - -  - - */
std::string	Channel::getName() const {return (this->_name);}

std::string	Channel::getTopic() const {return (this->_topic);}

std::vector<User> Channel::getLstUsers() const {return (this->_vecUsers);}


/*- - - - - - - - - - - - - - - - - SETTERS - - - - - - - - - - - -- - -  - - */
void	Channel::setName(std::string name) {this->_name = name;}

void	Channel::setTopic(std::string topic) {this->_topic = topic;}

/*- - - - - - - - - - - - - - - - - - ADD - - - - - - - - - - - - -- - -  - -*/

void	Channel::addUser(User &new_user)
{
	if (findUserInChannel(new_user) == false) {
		this->_vecUsers.push_back(new_user);
		this->_lstUsers[new_user] = VOICE;
	}
}

void	Channel::addMode(std::string new_mode)
{
	if (new_mode.size() != 1) {
		std::cout << "[ERROR] Non existing mode\n";
		return ;
	}
	if (new_mode.find_first_not_of("itko") != std::string::npos) {
		std::cout << "[ERROR] Ivalid mode\n";
		return ;
	}
	else {
		const char *mode = new_mode.c_str();
		this->_mode.push_back(mode[0]);
		std::cout << "Mode added\n";
	}
	//check that the mode that is send is a real mode
	// check that the mode is not already enable
	//if it is add the mode
}

/*- - - - - - - - - - - - - - - - - -DELETE - - - - - - - - - - -- - -  - - - */
void	Channel::deleteUser(User &user) {
	std::map<User, int>::iterator	it;

	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user.getNickname() == it->first.getNickname())
		{
			std::cout << it->first.getNickname() << " has been kicked of " << getName() <<std::endl;
			this->_lstUsers.erase(it);
			return ;
		}
	}
}

void	Channel::deleteMode(std::string mode)
{
	if (mode.size() != 1) {
		std::cout << "[ERROR] Non existing mode\n";
		return ;
	}
	if (mode.find_first_not_of("itko") != std::string::npos) {
		std::cout << "[ERROR] Ivalid mode\n";
		return ;
	}
	
	std::vector<char>::iterator	it;
	for (it = this->_mode.begin(); it != this->_mode.end(); it++) {
		if (*it == mode[0]) {
			this->_mode.erase(it);
			std::cout << "[ERROR] Mode successfully earased\n";
			return ;
		}
	}
	if (it == this->_mode.end())
		std::cout << "[ERROR] Mode was not enable\n";
	//check that the mode that is send is a real mode
	//check that this mode is activated for the channel
	//if it is add the mode
}

/*- - - - - - - - - - - - - - - - -  FIND - - - - - - - - - - - - -- - -  - - */
bool	Channel::findUserInChannel(User &user) const {
	
	std::map<User, int>::const_iterator	it;
	
	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user.getNickname() == it->first.getNickname())
			return (true);
	}
	return (false);
}

// bool	Channel::findUserInOperators(User &user) const {
	
// 	std::vector<User>::const_iterator	it;
	
// 	for (it = this->_lstOperators.begin(); it != this->_lstOperators.end(); it++) {
// 		if (user.getNickname() == it->getNickname())
// 			return (true);
// 	}
// 	return (false);
// }

//Channel name : no space, no coma, no control G/BELL
//All members of the chanel can invite users