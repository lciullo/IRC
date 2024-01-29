
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

void Server::mode(std::string msg, int fd) {
	// std::cout << msg << std::endl;

	std::vector<std::string>	cmd;
	std::string					target;
	std::string					protagonist;
	std::string					param;
	// char						sign = 'o';

	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getUsername();

// 	// checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS
	if (cmd.size() <= 1) {
		ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "MODE");
		return ;
	}

// 	if the channel we want to add the mode to does not exist -> ERR_NOSUCHCHANNEL
// 	if the target nickname does not exist on the server -> ERR_NOSUCHNICK
// 	if the mode string is not given -> RPL_CHANNELMODEIS and RPL_CREATIONTIME following

// 	Ckeck that the user who is doing the mode command have the proper rights
// 	print_vector(cmd);

	// int	i = 0;
	// print_vector(cmd);
	target = cmd[0];

	// checker que le channel existe -> -> ERR_NOSUCHCHANNEL
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(target)) == this->_lst_channel.end()) {
		std::cout << "ERROR no such channel\n";
		return ;
	}
	else {
		std::cout << "We fond the channel " << target << std::endl;
		current_channel = &it_serv->second;
		// if (current_channel->getStatus() == false) {
		// 	std::cout << "ERROR Channel is not in private no eed to ivite someoe everybody is free to join\n"; //a tester
		// }
	}

	cmd.erase(cmd.begin());
	// std::cout << std::endl;
	// print_vector(cmd);
	if (cmd[0][0] == '+') {
		// std::cout << "it's a plus" << std::endl;
		if (cmd.size() > 1)
			param = cmd[1];
		else
			param = "no param";
		if (cmd[0][1] == 'o')
			current_channel->addOperatorMode(param);
		else
			current_channel->addChannelMode(cmd[0][1], param);
	}
	else if (cmd[0][0] == '-') {
		// std::cout << "it's a minus" << std::endl;
		if (cmd.size() > 1)
			param = cmd[1];
		else
			param = "no param";
		if (cmd[0][1] == 'o')
			current_channel->deleteOperatorMode(param);
		else
			current_channel->deleteChannelMode(cmd[0][1], param);
	}
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

// //<channel/nickanme> <+/-> <mode> [parametre]

// // 1- premier arg == nom de channel ou nom de user
// // 2- peut importe checker qu'ils existe (pour user 
// //    checker qu'il fait bien parti du channel et qui a les bon droit)
// // 3- vector en checkant si c'est un plus ou un moins
// 		// ->si c'est un plus on envoie vers addMode
// 		// ->si c'est un moins on envoie vers deleteMode
// // 4 - quand c'est pour un user oblige -o donc juste on ajout le mode si possible