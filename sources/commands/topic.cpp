/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:56:17 by cllovio           #+#    #+#             */
/*   Updated: 2024/02/05 21:06:00 by cllovio          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Numerics.hpp"

void Server::topic(std::string msg, int fd)
{
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					protagonist;
	std::string					topic;
	std::time_t	now = time(0);
	// char *	time = ctime(&now);
	bool						operator_needed = false;
	
	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getUsername();
	
	if (cmd.size() <= 1) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "TOPIC");
		return ;
	}
	if (cmd.size() > 3) {
		for (std::vector<std::string>::iterator i = cmd.end(); cmd.size() > 4; i--) {
			cmd.erase(i);
		}
	}
	if (cmd.size() == 3) {
		if (cmd.at(cmd.size() - 1)[0] == ':')
			topic = cmd.at(cmd.size() - 1);
		cmd.erase(cmd.end());
	}

	channel_name = cmd[1];
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
		if (cmd[0] == "TOPIC")
			cmd.erase(cmd.begin());
		if (current_channel->getTopic().empty()) {
			RPL_NOTOPIC(this->GetUserByFd(fd), channel_name);
			return ;
		}
		else {
			RPL_TOPIC(this->GetUserByFd(fd), channel_name, current_channel->getTopic());
			RPL_TOPICWHOTIME(this->GetUserByFd(fd), channel_name, current_channel->getTopicInfo());
			return ;
		}
	}
	cmd.erase(cmd.begin());

	if (current_channel->getModestring().find('t') == std::string::npos)
		operator_needed = true;

	//Check that the user who want to invite is on the channel and have the good privilege
	std::map<User *, int>	lstUsrChannel = current_channel->getLstUsers();
	std::map<User *, int>::iterator	it_channel;
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == protagonist) {
			if (it_channel->second != OPERATOR && operator_needed == true) {
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
		topic = cmd.at(cmd.size() - 1);
		topic.erase(topic.begin());
	}
	current_channel->setTopic(topic, this->GetUserByFd(fd).getNickname() + " " + std::asctime(std::localtime(&now)));

	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		User user = *it_channel->first;
		RPL_TOPIC(user, channel_name, current_channel->getTopic());
		RPL_TOPICWHOTIME(user, channel_name, current_channel->getTopicInfo());
	}
}
