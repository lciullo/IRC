/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:36 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/14 20:23:25 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

void Server::kick(std::string msg, int fd) 
{
	int							kick_count = 0;
	std::string					channel_name;
	std::string					reason;
	std::vector<std::string>	cmd;
	std::vector<std::string>	all_ban;

	split_cmd(&cmd, msg);
	User	client = this->GetUserByFd(fd);

	//Check nbr parameters
	if (cmd.size() < 3) {
		ERR_NEEDMOREPARAMS(client, "KICK");
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
		else
			NOTICE(client, channel_name,  "The reason needs to begin by ':' (user was kicked without reason)");
		cmd.erase(cmd.end());
	}
	if (cmd.size() == 3) {
		split_arg(&all_ban, cmd[2]);
		cmd.erase(cmd.end());
	}
	if (cmd[0] == "KICK")
		cmd.erase(cmd.begin());
	
	//Check that the channel exist
	channel_name = cmd.at(0);
	if (channel_name[0] != '#' && channel_name[0] != '&') {
		ERR_BADCHANMASK(client, channel_name);
		return ;
	}

	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(client, channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;
	cmd.erase(cmd.begin());

	//Check that the client is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == client.getNickname()) {
			if (it_channel->second != OPERATOR) {
				ERR_CHANOPRIVSNEEDED(client, channel_name);
				return ;
			}
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		ERR_NOTONCHANNEL(client, channel_name);
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
			ERR_USERNOTINCHANNEL(client, channel_name, *it_cmd);
			continue ;
		}

		if (banned->getNickname() == client.getNickname()) {
			NOTICE(client, channel_name,  "[ERROR] Auto-kick not allowed");
			continue ;
		}
		
		//Send the kick message to all user on the channel
		for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
			User user = *it_channel->first;
			if (reason.empty())
				KICK_WITHOUT_REASON(user, client, channel_name, *it_cmd);
			else
				KICK_WITH_REASON(user, client, channel_name, *it_cmd, reason);
		}

		current_channel->deleteUser(*banned);
		banned->deleteChannel(channel_name);
		kick_count++;
	}
}
