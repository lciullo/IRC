/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:47:41 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/19 17:26:05 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, User &operators) : _name(name) {
	this->_lstOperators.push_back(operators);
	this->_lstUsers.push_back(operators);
}

std::string	Channel::getName() const {return (this->_name);}

std::string	Channel::getTopic() const {return (this->_topic);}

void	Channel::setName(std::string name) {this->_name = name;}

void	Channel::setTopic(std::string topic) {this->_topic = topic;}

void	Channel::addUser(User &new_user, User &operators)
{
	if (findUserInChannel(operators) == false) {
		return ;
	}
	if (findUserInChannel(new_user) == false) {
		this->_lstUsers.push_back(new_user);
	}
}

void	Channel::deleteUser(User &user) {
	std::vector<User>::iterator	it;

	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user.getNickname() == it->getNickname())
		{
			std::cout << it->getNickname() << " has been kicked of " << getName() <<std::endl;
			this->_lstUsers.erase(it);
			return ;
		}
	}
}

bool	Channel::findUserInChannel(User &user) const {
	
	std::vector<User>::const_iterator	it;
	
	for (it = this->_lstUsers.begin(); it != this->_lstUsers.end(); it++) {
		if (user.getNickname() == it->getNickname())
			return (true);
	}
	return (false);
}

bool	Channel::findUserInOperators(User &user) const {
	
	std::vector<User>::const_iterator	it;
	
	for (it = this->_lstOperators.begin(); it != this->_lstOperators.end(); it++) {
		if (user.getNickname() == it->getNickname())
			return (true);
	}
	return (false);
}

void	Channel::addMode(std::string new_mode, User &operators)
{
	if (findUserInOperators(operators) == false)
	{
		std::cout << "[ERROR] " << operators.getNickname() << " is not an operator\n";
		return ;
	}
	
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

void	Channel::deleteMode(std::string mode, User &operators)
{
	if (findUserInOperators(operators) == false)
	{
		std::cout << "[ERROR] " << operators.getNickname() << " is not an operator\n";
		return ;
	}
	
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

void	test()
{
	User	Jack("J", "Jack");
	User	Luc("L", "Luc");

	Channel	First("First", Luc);
	First.addUser(Jack, Luc);
	// First.deleteUser(Jack);
	First.addMode("i", Jack);
	First.deleteMode("a", Luc);
	First.deleteMode("i", Luc);
}

//Channel name : no space, no coma, no control G/BELL
//All members of the chanel can invite users