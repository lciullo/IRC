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
	std::vector<std::string>	all_ban;
	std::string					channel_name;
	std::string					reason;
	std::string					protagonist;
	int							kick_count = 0;

	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getNickname();
	
	// Check that the command have enough parameters
	if (cmd.size() < 3) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "KICK");
		return ;
	}

	if (cmd.size() > 4) {
		for (std::vector<std::string>::iterator i = cmd.end(); cmd.size() > 4; i--) {
			cmd.erase(i);
		}
	}
	if (cmd.size() == 4) {
		if (cmd.at(cmd.size() - 1)[0] == ':')
			reason = cmd.at(cmd.size() - 1);
		cmd.erase(cmd.end());
	}
	std::cout << cmd.size() << std::endl;
	if (cmd.size() == 3) {
		std::cout << "coucou2\n";
		split_arg(&all_ban, cmd[2]);
		std::cout << "coucou1\n";
		cmd.erase(cmd.end());
		std::cout << "coucou\n";
	}

	print_vector(all_ban);
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
		std::cout << it_channel->first->getNickname() << " ";
	}
	std::cout << std::endl;
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

	std::vector<std::string>::iterator	it_cmd;
	for (it_cmd = all_ban.begin(); it_cmd != all_ban.end(); it_cmd++) {
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
			continue ;
		}

		for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
			User user = *it_channel->first;
			if (reason.empty())
				KICK_WITHOUT_REASON(user, this->GetUserByFd(fd), channel_name, *it_cmd);
			else
				KICK_WITH_REASON(user, this->GetUserByFd(fd), channel_name, *it_cmd, reason);
		}

		current_channel->deleteUser(*banned);
		banned->deleteChannel(channel_name);
		kick_count++;
	}

	if (kick_count != 0)
		sendUserList(*current_channel);
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		std::cout << it_channel->first->getNickname() << " ";
	}
	std::cout << std::endl;
}

//quand je kick quelqu'un du channel vois pas les nouveau message et peut pas en envoye maistoujours acces
//une fois que la personne  ete kick quand elle essaie de join elle ne peut plus envoye de message sur le channel
//GARBAGE s'affiche avant mes message ?