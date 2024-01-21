// INVITE
	// <nickname> <channel>
	// L'invitation a bien ete envoye -> RPL_INVITING 
	// Commande different de 2 arguments -> ERR_NEEDMOREPARAMS
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// La personne qu'on essaye de kick ne fait pas parti du channel -> ERR_USERONCHANNEL