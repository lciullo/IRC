// TOPIC
	// <channel> [<topic>]
	// Commande inferieur a 1 arguments -> ERR_NEEDMOREPARAMS
		// commande : 1 ou 2 arguments
	// Le nom du channle fourni n'exite pas -> ERR_NOSUCHCHANNEL
	// La persoone qui essaye de faire l'action ne fait pas parti du channel -> ERR_NOTONCHANNEL
	// La personne qui vuet executer la commande n'a pas les bon privilege -> ERR_CHANOPRIVSNEEDED
	// Quand quelqu'un rejoins un channel qui n'a pas de topic -> RPL_NOTOPIC 
	// Quand quelqu'un rejoins un channel pour l'informer du topic -> RPL_TOPIC
	// Informe qui et qund le topic a ete set -> RPL_TOPICWHOTIME
		// Envoye apres RPL_TOPIC
