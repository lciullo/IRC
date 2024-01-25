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
	std::string					protagonist;

	split_cmd(&cmd, msg);
	channel_name = cmd.at(0);
	username = cmd.at(1);
	protagonist = this->_lst_usr[index - 1].getUsername();
	// print_vector(cmd);
	std::cout << msg << std::endl;
}

//pourquoi quand je fais kick il me met 2 fois le nom du chanel alors 
//que l'ai ecrit qu'une seule fois et pourqoi il rajoute : avant le 
//nom de l'user que je veux kick
//KICK #coucou #coucou :user
/kick #coucou user
//Pourquoi quand je deco et que je me reco au serveur, sans relancer hexchat,
// que j'essaie de faire la commande join je segfaulte ? 
// Quand j'ai 2 user d'ouvert