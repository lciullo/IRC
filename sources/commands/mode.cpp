
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
	std::cout << msg << std::endl;

	std::vector<std::string>	cmd;
	std::string					target;
	std::string					protagonist;
	// char						sign = 'o';

	split_cmd(&cmd, msg);
	protagonist = this->_lst_usr[index - 1].getUsername();

// 	// checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS
	if (cmd.size() <= 1) {
		ERR_NEEDMOREPARAMS(this->_lst_usr[index - 1], "INVITE");
		return ;
	}

// 	if the channel we want to add the mode to does not exist -> ERR_NOSUCHCHANNEL
// 	if the target nickname does not exist on the server -> ERR_NOSUCHNICK
// 	if the mode string is not given -> RPL_CHANNELMODEIS and RPL_CREATIONTIME following

// 	Ckeck that the user who is doing the mode command have the proper rights
// 	print_vector(cmd);

	// int	i = 0;
	print_vector(cmd);
	target = cmd[0];
	cmd.erase(cmd.begin());
	std::cout << std::endl;
	print_vector(cmd);
	// std::vector<std::string>::iterator	it;
	// while (cmd.size() > 0) {
	// 	if (it[0] == '#') {
	// 		target = it
	// 	}
	// 	else if (it[0] == '+') {
	// 		sign == '+';
	// 	}
	// 	else if (it[0] == '-') {
	// 		sign == '-';

	// 	}
	// 	else if (sign == 'o') {
	// 		target = it;
	// 	}
	// 	else if (sign == '-') {
	// 		//deletemode
	// 	}
	// 	else if (sign == '+') {
	// 		// add mode
	// 	}
	// }
}

//<channel/nickanme> <+/-> <mode> [parametre]

// 1- premier arg == nom de channel ou nom de user
// 2- peut importe checker qu'ils existe (pour user 
//    checker qu'il fait bien parti du channel et qui a les bon droit)
// 3- vector en checkant si c'est un plus ou un moins
		// ->si c'est un plus on envoie vers addMode
		// ->si c'est un moins on envoie vers deleteMode
// 4 - quand c'est pour un user oblige -o donc juste on ajout le mode si possible