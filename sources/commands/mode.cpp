
// MODE
	// <target> [<modestring> [<mode arguments>...]]
// -i
// -t 
// -k 
// -o
// -l

//on peut ajouter plusier mode d'un coup
// +oi-i+o

#include "Server.hpp"
#include "Numerics.hpp"

void Server::mode(std::string msg, int index) {
	(void) index;
	std::cout << msg << std::endl;

	std::vector<std::string>	cmd;
	std::string					target;
	std::string					mode;
	std::string					protagonist;

	split_cmd(&cmd, msg);
	target = cmd.at(0);
	mode = cmd.at(1);
	protagonist = this->_lst_usr[index - 1].getUsername();

	// // checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS
	// if (cmd.size() <= 1) {
	// 	ERR_NEEDMOREPARAMS(this->_lst_usr[index - 1], "INVITE");
	// 	return ;
	// }

	//if the channel we want to add the mode to does not exist -> ERR_NOSUCHCHANNEL
	//if the target nickname does not exist on the server -> ERR_NOSUCHNICK
	//if the mode string is not given -> RPL_CHANNELMODEIS and RPL_CREATIONTIME following

	//Ckeck that the user who is doing the mode command have the proper rights


	print_vector(cmd);
}

//<channel/nickanme> <+/-> <mode> [parametre]