/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:42:51 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 13:20:35 by cllovio          ###   ########lyon.fr   */
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
	std::string					protagonist;

	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getNickname();

	// Check that the command have enough parameters
	if (checkNbrParam(cmd.size(), 3, this->GetUserByFd(fd), cmd[0]) == false)
		return ;
	
	cmd.erase(cmd.begin());
	channel_name = cmd.at(1);
	guest_nickname = cmd.at(0);
	
	// Check that the channel exist
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;

	// Check that the guest exist and that is not already on the channel
	std::map<int, User>::iterator	it_serv_usr;
	User	*guest;
	for (it_serv_usr = this->_lst_usr.begin(); it_serv_usr != this->_lst_usr.end(); it_serv_usr++) {
		if (it_serv_usr->second.getNickname() == guest_nickname) {
			guest = &(it_serv_usr->second);
			break ;
		}
	}
	if (it_serv_usr == this->_lst_usr.end()) {
		std::cout << "ERROR Guest not in the serve\n"; //trouver la bonne erreur a renvoyer
		return ;
	}

	//Check that the user who want to invite is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == protagonist) {
			if (it_channel->second != OPERATOR && current_channel->getStatus() == true) {
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
	
	//Check that the person we are trying to add is not already on
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == guest_nickname) {
			ERR_USERONCHANNEL(this->GetUserByFd(fd), channel_name, guest_nickname);
			return ;
		}
	}

	current_channel->addUserToWaitlist(guest);
	RPL_INVITING(this->GetUserByFd(fd), channel_name, guest_nickname);
	INVITE_MESSAGE(guest, channel_name);
}

bool	checkNbrParam(size_t cmd_size, size_t size, User &user, std::string cmd){
	if (cmd_size < size) {
		ERR_NEEDMOREPARAMS(user, cmd);
		return (false);
	}
	return (true);
}
