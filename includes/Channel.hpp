/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:19 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/14 20:23:34 by cllovio          ###   ########lyon.fr   */
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
		int						_nbrUser;
		int						_nbrUserMax;
		bool					_private;
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		std::string				_topicInfo;
		std::vector<char>		_mode;
		std::vector<User *>		_waitlist;
		std::vector<User *>		_vecUsers;
		std::map<User *, int>	_lstUsers;

	public :
		Channel();
		Channel(std::string name, User *operators);
		Channel(const Channel &channel);
		Channel &operator=(const Channel &channel);
		
		//Getters
		int						getNbrUser() const;
		int						getNbrUserMax() const;
		bool					getStatus() const;
		std::string				getName() const;
		std::string				getTopic() const;
		std::string				getPassword() const;
		std::string				getTopicInfo() const;
		std::string				getModestring() const;
		std::vector<User *>		getVecUsers() const;
		std::vector<User *>		getwaitlist() const;
		std::map<User *, int>	getLstUsers() const;

		//Setters
		void					setTopic(std::string topic, std::string nickSetter);
		
		//Add
		void					addUser(User *new_user);
		bool					addMode(char new_mode, std::string param);
		void					addTopic(std::string new_topic);
		void					addUserToWaitlist(User *guest);
		
		//Delete
		void					deleteUser(User &user);
		bool					deleteMode(char mode, std::string param);
		void					deleteUserToWaitlist(User user);
		
		//Find
		bool					findUser(User *user) const;
		bool					findInWaitList(User user) const;
};

void	split_cmd(std::vector<std::string> *cmd, std::string msg);
void	print_vector(std::vector<std::string> cmd);

#endif