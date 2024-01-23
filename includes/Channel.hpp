/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:19 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/23 15:43:10 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <bits/stdc++.h>
# include <map>
# include "User.hpp"

enum {
	VOICE = 0,
	OPERATOR = 1,
};

class Channel
{
	private :
		std::string			_name;
		std::string			_topic;
		std::vector<char>	_mode;
		std::vector<User *>	_waitlist;
		std::map<User *, int>	_lstUsers;
		std::vector<User *>	_vecUsers;

	public :
		Channel(std::string name, User *operators);
		Channel(const Channel &channel);
		
		//Getters
		std::string		getName() const;
		std::string		getTopic() const;
		std::vector<User *> getLstUsers() const;
		
		//Setters
		void			setName(std::string name);
		void			setTopic(std::string topic);
		
		//Add
		void			addUser(User *new_user);
		void			addMode(std::string new_mode); // or a char?
		void			addTopic(std::string new_topic);
		
		//Delete
		void			deleteUser(User &user);
		void			deleteMode(std::string mode);
		
		//Find
		bool			findUser(User *user) const;
		bool			findOperators(User &user) const;
};

#endif