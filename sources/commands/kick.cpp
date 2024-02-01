/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:36 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 16:33:37 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

void Server::kick(std::string msg, int fd) {
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					username;
	std::string					reason;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getUsername();
	if (cmd.size() == 4)
		reason = cmd.at(3);
	
	if (cmd.size() <= 1) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "KICK");
		return ;
	}
	cmd.erase(cmd.begin());
	channel_name = cmd.at(0);
	username = cmd.at(1);
	
	// Check that the channel exist
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;

	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	//Si cette personne est dans le channel checker quelle a les bon priviliege -> ERR_CHANOPRIVSNEEDED
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == protagonist) {
			if (it_channel->second != OPERATOR) {
				std::cout << "ERROR User is in the channel but does not have the right role\n";
				return ;
			}
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		std::cout << "ERROR User not in the channel\n";
		return ;
	}

	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL
	User	*guest;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == username) { 
			guest = it_channel->first;
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		std::cout << "ERROR User not in the channel\n";
		return ;
	}

	current_channel->deleteUser(*guest);
}

// KICK
	// <channel> <user> *( "," <user> ) [<comment>]
	// Si commande inferieur a 2 argument -> ERR_NEEDMOREPARAMS
		// commande : 2 ou 3 arguments
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL 
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL