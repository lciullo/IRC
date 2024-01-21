// KICK
	// <channel> <user> *( "," <user> ) [<comment>]
	// Si commande inferieur a 2 argument -> ERR_NEEDMOREPARAMS
		// commande : 2 ou 3 arguments
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL 
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL 