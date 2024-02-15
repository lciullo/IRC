/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:42:51 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/05 23:04:22 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

bool	checkNbrParam(size_t cmd_size, size_t size, User &user, std::string cmd);

void Server::invite(std::string msg, int fd)
{
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					guest_nickname;

	split_cmd(&cmd, msg);
	User	client = this->GetUserByFd(fd);

	// Check that the command size
	if (cmd.size() == 1) {
		std::string	invite_list;
		std::vector<std::string> invite = client.getInvite();
		std::vector<std::string>::iterator	it;
		for (it = invite.begin(); it != invite.end(); it++)
			invite_list += *it + " ";
		RPL_INVITELIST(client, invite_list);
		return ;
	}

	if (cmd.size() < 3) {
		ERR_NEEDMOREPARAMS(client, "INVITE");
		return ;
	}
	if (cmd.size() > 3) {
		for (std::vector<std::string>::iterator i = cmd.end(); cmd.size() > 4; i--)
			cmd.erase(i);
	}
	
	if (cmd[0] == "INVITE") {cmd.erase(cmd.begin());}
	guest_nickname = cmd.at(0);
	channel_name = cmd.at(1);
	
	// Check that the channel exist
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(client, channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;

	// Check that the guest exist and that is not already on the channel
	User	*guest;
	std::map<int, User>::iterator	it_serv_usr;
	for (it_serv_usr = this->_lst_usr.begin(); it_serv_usr != this->_lst_usr.end(); it_serv_usr++) {
		if (it_serv_usr->second.getNickname() == guest_nickname) {
			guest = &(it_serv_usr->second);
			break ;
		}
	}
	if (it_serv_usr == this->_lst_usr.end()) {
		NOTICE(client, channel_name, "[ERROR] The user you are trying to invite does not exist");
		return ;
	}

	//Check that the client is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == client.getNickname()) {
			if (it_channel->second != OPERATOR && current_channel->getStatus() == true) {
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
	
	//Check that the person we are trying to add is not already on
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == guest_nickname) {
			ERR_USERONCHANNEL(client, channel_name, guest_nickname);
			return ;
		}
	}

	current_channel->addUserToWaitlist(guest);
	guest->addInvite(channel_name);

	RPL_INVITING(client, channel_name, guest_nickname);
	INVITE_MESSAGE(guest, channel_name, client);
}
