/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:45:08 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:45 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

bool	checkparam(char mode, std::string param, std::map<User *, int> lstUsers_channel, std::string channel_name, User &user);

void Server::mode(std::string msg, int fd) {
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					protagonist;
	std::string					param;
	std::string					modestring;
	char						sign;

	std::cout << msg << std::endl;
	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).findUsername();
	
	if (cmd[0] == "MODE")
		cmd.erase(cmd.begin());
	
	// Check that the channel exist
	if (cmd.size() > 0)
		channel_name = cmd[0];
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}
	else
		current_channel = &it_serv->second;
	cmd.erase(cmd.begin());

	if (!cmd.empty() && cmd[0].size()!= 0) {
		modestring = cmd[0];
		cmd.erase(cmd.begin());
	}
	else {
		RPL_CHANNELMODEIS(this->GetUserByFd(fd), channel_name, current_channel->getModestring());
		RPL_CREATIONTIME(this->GetUserByFd(fd), channel_name, current_channel->getCreationTimeChannel());
		return ;
	}

	//Check that the user who want to invite is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->findUsername() == protagonist) {
			if (it_channel->second == VOICE) {
				ERR_CHANOPRIVSNEEDED(this->GetUserByFd(fd), channel_name);;
				return ;
			}
			break ;
		}
	}
	if (it_channel == lstUsrChannel.end()) {
		ERR_NOTONCHANNEL(this->GetUserByFd(fd), channel_name);
		return ;
	}

	//Check the format of the mode string
	if (modestring[0] == '+' || modestring[0] == '-') {
		sign = modestring[0];
		modestring.erase(modestring.begin());
	}
	else {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "MODE");
		return ;
	}

	//Check the mode the param and add/delte the mode
	std::string::iterator	it;
	unsigned long	i = 0;
	for (it = modestring.begin(); it != modestring.end(); it++) {
		if (*it == '+' || *it == '-') {
			sign = *it;
			continue ;
		}
		else if (isMode(*it) == false) {
			ERR_UNKNOWNMODE(this->GetUserByFd(fd), *it);
			return ;
		}

		if (*it == 'o' || (sign == '+' && (*it == 'k' || *it == 'l'))) {
			if (i < cmd.size()) {
				param = cmd.at(i);
				i++;
				if (checkparam(*it, param, current_channel->getLstUsers(), channel_name, this->GetUserByFd(fd)) == false)
					continue ;
			}
			else {
				ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "MODE");
				continue ;
			}
		}

		if (sign == '+')
			current_channel->addMode(*it, param);
		else if (sign == '-')
			current_channel->deleteMode(*it, param);
			
		param.clear();
	}
}

bool	checkparam(char mode, std::string param, std::map<User *, int> lstUsers_channel, std::string channel_name, User &user) {
	if (mode == 'l') {
		unsigned long i;
		for (i = 0; i < param.size(); i++) {
			if (!isdigit(param[i])) {
				ERR_INVALIDMODEPARAM(user, channel_name, mode, param, "only numbers are accepted");
				return (false);
			}
		}
	}

	if (mode == 'o') {
		std::map<User *, int>::iterator	it_lstUsers;
		for (it_lstUsers = lstUsers_channel.begin(); it_lstUsers != lstUsers_channel.end(); it_lstUsers++) {
			if (it_lstUsers->first->findNickname() == param)
				break ;
		}
		if (it_lstUsers == lstUsers_channel.end()) {
			ERR_INVALIDMODEPARAM(user, channel_name, mode, param, "User not in the channel");
			return (false);
		}
	}

	if (mode == 'k') {
		if (param.find_first_of(" \t\n\r\f\v", 0) != std::string::npos) {
			ERR_INVALIDMODEPARAM(user, channel_name, mode, param, "Password should not have spacces");
			return (false);
		}
	}
	return (true);
}