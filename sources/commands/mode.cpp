
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

bool	isMode(char mode) {
	if (mode == 'i' || mode == 't' || mode == 'k' || mode == 'o' || mode == 'l')
		return (true);
	return (false);
}
void Server::mode(std::string msg, int fd) {
	// std::cout << msg << std::endl;

	std::vector<std::string>	cmd;
	std::string					channel;
	std::string					protagonist;
	std::string					param;
	std::string					modestring;
	char						sign;

	split_cmd(&cmd, msg);
	protagonist = this->GetUserByFd(fd).getUsername();
	// checker que la commnade est de la bonne taille -> ERR_NEEDMOREPARAMS
	// if (cmd.size() <= 1) {
	// 	ERR_NEEDMOREPARAMS(this->GetUserByFd(fd), "MODE");
	// 	return ;
	// }

// 	if the channel we want to add the mode to does not exist -> ERR_NOSUCHCHANNEL
// 	if the target nickname does not exist on the server -> ERR_NOSUCHNICK
// 	if the mode string is not given -> RPL_CHANNELMODEIS and RPL_CREATIONTIME following

// 	Ckeck that the user who is doing the mode command have the proper rights
	print_vector(cmd);

	// checker que le channel existe -> -> ERR_NOSUCHCHANNEL
	Channel						*current_channel;
	std::map<std::string, Channel>::iterator	it_serv;
	if ((it_serv = this->_lst_channel.find(cmd[0])) == this->_lst_channel.end()) {
		std::cout << "ERROR no such channel\n";
		return ;
	}
	else {
		current_channel = &it_serv->second;
		// if (current_channel->getStatus() == false) {
		// 	std::cout << "ERROR Channel is not in private no eed to ivite someoe everybody is free to join\n"; //a tester
		// }
	}
	cmd.erase(cmd.begin());

	//checker que le client a les bon droit pour changer les modes
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

	if (!cmd.empty() && cmd[0].size()!= 0) {
		modestring = cmd[0];
		cmd.erase(cmd.begin());
	}
	else {
		std::cout << "ERROR no mode string\n";
		return ;
	}

	if (modestring[0] == '+' || modestring[0] == '-') {
		sign = modestring[0];
		modestring.erase(modestring.begin());
	}
	else {
		std::cout << "ERROR Modestring wrong format\n";
		return ;
	}

	std::cout << modestring << std::endl;
	print_vector(cmd);
	std::string::iterator	it;
	unsigned long	i = 0;
	for (it = modestring.begin(); it != modestring.end(); it++) {
		if (*it == '+' || *it == '-') {
			sign = *it;
			continue ;
		}
		else if (isMode(*it) == false) {
			std::cout << "Error wrong format of modestring\n";
			return ;
		}

		std::cout << "The mode is :" << *it << std::endl;
		if (*it == 'o' || *it == 'k' || *it == 'l') {
			if (i < cmd.size()) {
				param = cmd.at(i);
				i++;
			}
			else {
				std::cout << "ERROR the mode need an argument\n";
				continue ;
			}
			param.clear();
		}

		switch (sign) {
			case '+' : {current_channel->addChannelMode(*it, param);}
			case '-' : {current_channel->deleteChannelMode(*it, param);}
		}

		// if (*it == 'o')
		// 	current_channel->addOperatorMode(param);
		// else
		// 	current_channel->addChannelMode(*it, param);
	}

	// if (cmd[0][0] == '+') {
	// 	if (cmd.size() > 1)
	// 		param = cmd[1];
	// 	else
	// 		param = "no param";
	// }
	// else if (cmd[0][0] == '-') {
	// 	if (cmd.size() > 1)
	// 		param = cmd[1];
	// 	else
	// 		param = "no param";
	// 	if (cmd[0][1] == 'o')
	// 		current_channel->deleteOperatorMode(param);
	// 	else
	// 		current_channel->deleteChannelMode(cmd[0][1], param);
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