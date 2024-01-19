/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:19 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/19 17:21:00 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
#include <bits/stdc++.h>
# include "User.hpp"

class Channel
{
	private :
		std::string			_name;
		std::string			_topic;
		std::vector<char>	_mode;
		std::vector<User>	_lstUsers;
		std::vector<User>	_lstOperators;

	public :
		Channel(std::string name, User &operators);
		
		std::string		getName() const;
		std::string		getTopic() const;
		void			setName(std::string name);
		void			setTopic(std::string topic);
		void			addUser(User &new_user, User &operators);
		void			deleteUser(User &user);
		void			addMode(std::string new_mode, User &operators); // or a char?
		void			deleteMode(std::string mode, User &operators);
		bool			findUserInChannel(User &user) const;
		bool			findUserInOperators(User &user) const;

		//KICK
		//INVITE
		//TOPIC
		//MODE
};

void	test();

#endif