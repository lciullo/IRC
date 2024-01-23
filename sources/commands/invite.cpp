// INVITE
	// <nickname> <channel>
	// L'invitation a bien ete envoye -> RPL_INVITING 

	//faire idx - 1 dans lst_user pour avoir le user

	// Launch server
	//

// /JOIN #nom_server

#include "Server.hpp"
#include "Numerics.hpp"
void	split_cmd(std::vector<std::string> *cmd, std::string msg);
void	print_vector(std::vector<std::string> cmd);

void Server::invite(std::string msg, int index)
{
	std::vector<std::string>	cmd;
	(void)index;

	split_cmd(&cmd, msg);
	if (cmd.size() == 2) {
		ERR_NEEDMOREPARAMS(this->_lst_usr[index - 1], "INVITE");
	}
	// checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS

	// checker que le channel existe -> -> ERR_NOSUCHCHANNEL

	//checker que la personne qui veut ajouter est bien dans le serveur -> ERR_NOTONCHANNEL


	//Si cette personne est dans le channel checker quelle a les bon priviliege -> ERR_CHANOPRIVSNEEDED
	
	//checker que la personne qu'on veut ajouter n'est pas deja le serveur -> ERR_USERONCHANNEL

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

	while (msg.size() != 0)
	{
		begin = msg.find_first_not_of(" ");
		end = msg.find(" ", begin);

		str = msg.substr(begin, end);
		if (str == "INVITE") {
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