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

	std::cout << msg << std::endl;
	split_cmd(&cmd, msg);
	channel_name = cmd[0];
	protagonist = this->GetUserByFd(fd).getUsername();
	
	if (cmd.size() < 1) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "INVITE");
		return ;
	}
	cmd.erase(cmd.begin());
	print_vector(cmd);

	// checker que le channel existe -> -> ERR_NOSUCHCHANNEL
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		std::cout << "ERROR no such channel\n";
		return ;
	}
	else {
		std::cout << "We fond the channel " << channel_name << std::endl;
		current_channel = &it_serv->second;
		if (current_channel->getStatus() == false) {
			std::cout << "ERROR Channel is not in private no eed to ivite someoe everybody is free to join\n"; //a tester
		}
	}
	
	//checker que la personne qui veut ajouter est bien dans le serveur -> ERR_NOTONCHANNEL
	//Si cette personne est dans le channel checker quelle a les bon priviliege -> ERR_CHANOPRIVSNEEDED
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == protagonist) {
			if (it_channel->second != OPERATOR) {
				std::cout << "ERROR User is in the channel but does not have the right role\n";
				return ;
			}
			std::cout << "User is in the channel and have the good right" << std::endl;
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		std::cout << "ERROR User not in the channel\n";
		return ;
	}
	
}

// TOPIC
	// <channel> [<topic>]
	// Commande inferieur a 1 arguments -> ERR_NEEDMOREPARAMS
		// commande : 1 ou 2 arguments
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// Quand quelqu'un rejoins un channel qui n'a pas de topic -> RPL_NOTOPIC 
	// Quand quelqu'un rejoins un channel pour l'informer du topic -> RPL_TOPIC
	// Informe qui et qund le topic a ete set -> RPL_TOPICWHOTIME
		// Envoye apres RPL_TOPIC