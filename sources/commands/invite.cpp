// INVITE
	// <nickname> <channel>
	// L'invitation a bien ete envoye -> RPL_INVITING 

	//faire idx - 1 dans lst_user pour avoir le user

	// Launch server
	//

// /JOIN #nom_server

#include "Server.hpp"
#include "Numerics.hpp"

User &	User::operator=(const User &obj){
	this->_nickname = obj._nickname;
	this->_channel = obj._channel;
	this->_username = obj._username;
	this->_fd = obj._fd;
	this->_isCreate = obj._isCreate;

	return (*this);
}

void Server::invite(std::string msg, int fd)
{
	std::vector<std::string>	cmd;
	std::string					channel_name;
	std::string					guest_username;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	channel_name = cmd.at(1);
	guest_username = cmd.at(0);
	protagonist = this->GetUserByFd(fd).getUsername();

	std::cout << "\"" << guest_username[guest_username.size() - 1] << "\"" << std::endl; 
	// checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS
	if (cmd.size() != 2) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "INVITE");
		return ;
	}

	// checker que le channel existe -> -> ERR_NOSUCHCHANNEL
	std::map<std::string, Channel>::iterator	it_serv;
	Channel						*current_channel;
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

	std::map<int, User>::iterator	it_serv_usr;
	User	*guest;
	for (it_serv_usr = this->_lst_usr.begin(); it_serv_usr != this->_lst_usr.end(); it_serv_usr++)
	{
		if (it_serv_usr->second.getUsername() == guest_username) {
			guest = &(it_serv_usr->second);
			std::cout << "Guest is in the server\n";
			break ;
		}
	}
	if (it_serv_usr == this->_lst_usr.end()) {
		std::cout << "ERROR Guest not in the serve\n";
		return ;
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
	
	//checker que la personne qu'on veut ajouter n'est pas deja le serveur -> ERR_USERONCHANNEL
	for (it_channel = lstUsrChannel.begin(); it_channel != lstUsrChannel.end(); it_channel++) {
		if (it_channel->first->getUsername() == guest_username) {
			std::cout << "ERROR User who you are trying to invite is already on the channel\n";
			return ;
		}
	}

	current_channel->addUserToWaitlist(guest);
	std::cout << "SUCCES Guest invited to guest list\n";
	//send message to new gust and to inviter
	//checker qu'il n'a pas deja ete invite avant
	//la personne a ete invite

}

// Quand j'essaie d'invite  et que je mets qu'un argument automatiquement un autre argument s'ajoute

void	send_msg(User user, std::string msg)
{
	size_t byteSent = 0;

	while (byteSent < msg.length())
	{
		std::cout << msg << std::endl;
		long len = send(user.getFd(), msg.c_str(), msg.size(), 0);
		if (len < 0)
			break ;
		byteSent += len;
	}
}

void	split_cmd(std::vector<std::string> *cmd, std::string msg)
{
	size_t	begin;
	size_t	end;
	std::string	str;
	std::string	whitespace = " \t\n\r\f\v";
	size_t	last_non_space;

	while (msg.size() != 0)
	{
		begin = msg.find_first_not_of(" ");
		end = msg.find(" ", begin);

		str = msg.substr(begin, end);
		if ((last_non_space = str.find_last_not_of(whitespace)) != std::string::npos)
			str.erase(last_non_space + 1);
		if (str == "INVITE" || str == "KICK") {
			msg.erase(0, end);
			continue ;
		}
		cmd->push_back(str.c_str());

		msg.erase(0, end);
	}
	std::cout << std::endl;
}

void	print_vector(std::vector<std::string> cmd)
{
	std::vector<std::string>::iterator	it;
	for (it = cmd.begin(); it != cmd.end(); it++) {
		std::cout << *it << std::endl;
	}
}