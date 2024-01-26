// KICK
	// <channel> <user> *( "," <user> ) [<comment>]
	// Si commande inferieur a 2 argument -> ERR_NEEDMOREPARAMS
		// commande : 2 ou 3 arguments
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL 
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL

#include "Server.hpp"
#include "Numerics.hpp"

void Server::kick(std::string msg, int index)
{
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					username;
	std::string					reason;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	channel_name = cmd.at(0);
	username = cmd.at(1);
	protagonist = this->_lst_usr[index - 1].getUsername();
	if (cmd.size() == 3)
		reason = cmd.at(3);
	
	if (cmd.size() <= 1) {
		ERR_NEEDMOREPARAMS(this->_lst_usr[index - 1], "INVITE");
		return ;
	}


	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL
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
			std::cout << "User is in the channel and have the good right" << std::endl;
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
			std::cout << "The person we want to kick is on the channel\n";
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
