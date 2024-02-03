/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:56:17 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 10:47:18 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

void Server::topic(std::string msg, int fd)
{
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	channel_name = cmd[1];
	protagonist = this->GetUserByFd(fd).getUsername();
	
	if (cmd.size() < 1) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "TOPIC");
		return ;
	}

	// Check that the channel exist
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	else {
		current_channel = &it_serv->second;
	}

	if (cmd.size() == 1) {
		if (current_channel->getTopic().empty()) {
			RPL_NOTOPIC(this->GetUserByFd(fd), channel_name);
			return ;
		}
		else {
			RPL_TOPIC(this->GetUserByFd(fd), channel_name, current_channel->getTopic());
			//RPL_TOPICWHOTIME
			return ;
		}
	}
	cmd.erase(cmd.begin());

	//Check that the user who want to invite is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == protagonist) {
			if (it_channel->second != OPERATOR) {
				ERR_CHANOPRIVSNEEDED(this->GetUserByFd(fd), channel_name);
				return ;
			}
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		ERR_NOTONCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	//envoyer un message a tout le monde avec send TOPIC command
}

// TOPIC
	// <channel> [<topic>]
	// Commande inferieur a 1 arguments -> ERR_NEEDMOREPARAMS
		// commande : 1 ou 2 arguments
	// Informe qui et qund le topic a ete set -> RPL_TOPICWHOTIME
		// Envoye apres RPL_TOPIC