// INVITE
	// <nickname> <channel>
	// L'invitation a bien ete envoye -> RPL_INVITING 
	// Commande different de 2 arguments -> ERR_NEEDMOREPARAMS
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL

	//faire idx - 1 dans lst_user pour avoir le user

	// Launch server
	//

// /JOIN #nom_server

#include "Server.hpp"

void	split_cmd(std::vector<std::string> *cmd, std::string msg);
void	print_vector(std::vector<std::string> cmd);

void Server::invite(std::string msg, int index)
{
	std::vector<std::string>	cmd;
	(void)index;

	split_cmd(&cmd, msg);
	print_vector(cmd);
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
		std::cout << str << std::endl;
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