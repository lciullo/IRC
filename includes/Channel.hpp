/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:19 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 13:38:13 by cllovio          ###   ########lyon.fr   */
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
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		std::vector<char>		_mode;
		std::vector<User *>		_waitlist;
		std::map<User *, int>	_lstUsers;
		std::vector<User *>		_vecUsers;
		bool					_private;
		int						_nbrUser;
		int						_nbrUserMax;
		std::string				_creationTimeChannel;
		std::string				_creationTimeTopic;
		std::string				_nickSetterTopic;

	public :
		Channel();
		Channel(std::string name, User *operators, std::string creation_time);
		Channel(const Channel &channel);
		Channel &operator=(const Channel &channel);
		
		//Getters
		std::string				getName() const;
		std::string				getTopic() const;
		std::map<User *, int>	getLstUsers() const;
		std::vector<User *>		getVecUsers() const;
		bool					getStatus() const;
		int						getNbrUser() const;
		int						getNbrUserMax() const;
		std::string				getPassword() const;
		std::string				getModestring() const;
		std::string				getCreationTimeChannel() const;
		
		//Setters
		void			setName(std::string name);
		void			setTopic(std::string topic);
		
		//Add
		void			addUser(User *new_user);
		void			addMode(char new_mode, std::string param);
		void			addTopic(std::string new_topic);
		void			addUserToWaitlist(User *guest);
		
		//Delete
		void			deleteUser(User &user);
		void			deleteMode(char mode, std::string param);
		void			deleteUserToWaitlist(User user);
		
		//Find
		bool			findUser(User *user) const;
		bool			findOperators(User &user) const;
		bool			findInWaitList(User user) const;
};

void	split_cmd(std::vector<std::string> *cmd, std::string msg);
void	print_vector(std::vector<std::string> cmd);

#endif