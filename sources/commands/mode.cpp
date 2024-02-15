/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:45:08 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/14 16:31:19 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

bool	checkparam(char mode, std::string param, std::map<User *, int> lstUsers_channel, std::string channel_name, User &user);

void Server::mode(std::string msg, int fd) {
	char						sign;
	std::string					channel_name;
	std::string					param;
	std::string					modestring;
	std::string					param_used;
	std::string					mode_added;
	std::vector<std::string>	cmd;

	split_cmd(&cmd, msg);
	User	client =this->GetUserByFd(fd);;
	
	if (cmd.size() < 2) {
		ERR_NEEDMOREPARAMS(client, "INVITE");
		return ;
	}

	if (cmd[0] == "MODE")
		cmd.erase(cmd.begin());
	
	// Check that the channel exist
	if (cmd.size() > 0)
		channel_name = cmd[0];
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(channel_name)) == this->_lst_channel.end()) {
		ERR_NOSUCHCHANNEL(client, channel_name);
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
		RPL_CHANNELMODEIS(client, channel_name, current_channel->getModestring());
		return ;
	}

	//Check that the client is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getNickname() == client.getNickname()) {
			if (it_channel->second == VOICE) {
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

	//Check the format of the mode string
	if (modestring[0] == '+' || modestring[0] == '-') {
		sign = modestring[0];
		// modestring.erase(modestring.begin());
	}
	else {
		NOTICE(client, channel_name, "[ERROR] <modestring> needs to begin by '+' or '-'");
		return ;
	}

	//Check the mode, the param and add/delte the mode
	std::string::iterator	it;
	unsigned long	i = 0;
	for (it = modestring.begin(); it != modestring.end(); it++) {
		if (*it == '+' || *it == '-') {
			sign = *it;
			mode_added.push_back(*it);
			continue ;
		}
		else if (isMode(*it) == false) {
			ERR_UNKNOWNMODE(client, *it);
			return ;
		}

		if (*it == 'o' || (sign == '+' && (*it == 'k' || *it == 'l'))) {
			if (i < cmd.size()) {
				param = cmd.at(i);
				i++;
				if (checkparam(*it, param, current_channel->getLstUsers(), channel_name, client) == false) {
					
					continue ;
				}
				if (*it == 'l' && atoi(param.c_str()) < current_channel->getNbrUser()) {
					
					NOTICE(client, channel_name,  "User limit must be superiror to the number of user that are already on the channel");
					continue ;
				}
				param_used += " " + param;
			}
			else {
				
				NOTICE(client, channel_name, *it + " needs a parameters");
				continue ;
			}
		}

		if (sign == '+') {
			if (current_channel->addMode(*it, param) == true)
				mode_added.push_back(*it);
		}
		else if (sign == '-') {
			if (current_channel->deleteMode(*it, param) == true)
				mode_added.push_back(*it);
		}
		param.clear();
	}

	bool sign_bool = false;
	for (it = mode_added.begin(); it != mode_added.end(); it++) {
		if ((*it == '+' || *it == '-') && sign_bool == true) {
			if (it > mode_added.begin())
				it--;
			mode_added.erase(it);
		}
		else if (*it == '+' || *it == '-') {
			sign_bool = true;
		}
		else
			sign_bool = false;
	}
	if (sign_bool == true)
	{
		if (it > mode_added.begin())
			it--;
		mode_added.erase(it);
	}
	mode_added += param_used;
	if (mode_added.empty())
		return ;
	
	//Send the mode message to all user on the channel
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		User user = *it_channel->first;
		MODE_MESSAGE(user, client, channel_name, mode_added);
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
			if (it_lstUsers->first->getNickname() == param) {

				break ;
			}
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