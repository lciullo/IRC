/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:19 by cllovio           #+#    #+#             */
/*   Updated: 2024/01/18 16:07:37 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <list>
# include "User.hpp"

class Channel
{
	private :
		std::string		_name;
		std::string		_topic;
		// std::list<User>	_list_users;
		// std::list<User>	_list_operators;

	public :
		Channel(std::string name, std::string topic);
		
		std::string		getName() const;
		std::string		getTopic() const;
		void			setName(std::string name);
		void			setTopic(std::string topic);
		
		//KICK
		//INVITE
		//TOPIC
		//MODE
};

#endif