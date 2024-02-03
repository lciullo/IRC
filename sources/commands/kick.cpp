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
	std::string					reason;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	print_vector(cmd);
	protagonist = this->GetUserByFd(fd).getNickname();
	
	// Check that the command have enough parameters
	if (cmd.size() == 4)
		reason = cmd.at(3);
	
	if (cmd.size() < 3) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "KICK");
		return ;
	}
	cmd.erase(cmd.begin());
	channel_name = cmd.at(0);
	
	// Check that the channel exist
	if (channel_name[0] != '#' && channel_name[0] != '&') {
		ERR_BADCHANMASK(this->GetUserByFd(fd), channel_name);
		return ;
	}

	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;
	cmd.erase(cmd.begin());

	//Check that the user who want to invite is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == protagonist) {
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

	if (cmd.at(cmd.size() - 1)[0] == ':') {
		reason = cmd.at(cmd.size() - 1);
		cmd.erase(cmd.end());
		reason.erase(reason.begin());
	}
	
	std::vector<std::string>::iterator	it_cmd;
	for (it_cmd = cmd.begin(), it_cmd != cmd.end(), it_cmd++) {
		//Check that the person we are trying to kick is on the channel
		User	*banned;
		for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
			if (it_channel->first->getNickname() == *it_cmd) { 
				banned = it_channel->first;
				break ;
			}
		}
		if (it_channel == lstUsrChannel.end()) {
			ERR_USERNOTINCHANNEL(this->GetUserByFd(fd), channel_name, *it_cmd);
			return ;
		}
		current_channel->deleteUser(*banned);
		banned->deleteChannel(channel_name);
		//ENVOYER UN MESSAGE A TOUT LES MEMBRES DU SERVEUR COMME QUOI QUELQU'UN A ETE KICK
	}
}
