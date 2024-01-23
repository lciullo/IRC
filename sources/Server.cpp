
#include "Server.hpp"
class User;


Server::Server(int port, std::string password)
{
	this->_address = INADDR_ANY;
	this->_port = port;
	this->_password = password;
	bzero((char *) &this->_serv_addr, sizeof(this->_serv_addr));
	this->_serv_addr.sin_family = AF_INET;
	this->_serv_addr.sin_port = htons(port);
	this->_serv_addr.sin_addr.s_addr = INADDR_ANY;
}

void Server::launch()
{
	char buffer[256];
	int n;
	int opt = 1;
	int level = 0;

	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
		exit(EXIT_FAILURE);
	if (this->_socketfd < 0)
	{
		std::cout << "[ERROR] Creation of socket failed";
		return;
	}
	if (bind(this->_socketfd, (struct sockaddr *) &this->_serv_addr, sizeof(this->_serv_addr)))
	{
		std::cout << "[ERROR] Bind socket failed";
		return;
	}
	struct pollfd first;
	first.fd = this->_socketfd;
	first.events = POLLIN;
	this->_lst_fd.push_back(first);
	listen(this->_socketfd,5);
	while (1)
	{
		if (poll(&this->_lst_fd[0], this->_lst_fd.size(), -1) >= 0)
		{
			if (this->_lst_fd[0].revents & POLLIN)
			{
				std::cout << "NEW USER" << std::endl;
				this->create_user();
			}
			for (int i=1; i < (int)this->_lst_fd.size(); i++) 
			{
				if (this->_lst_fd[i].revents & POLLIN) {
					bzero(buffer,256);
					n = read(this->_lst_fd[i].fd,buffer,255);
					if (n < 0) 
						std::cout << "ERROR writing to socket" << std::endl;
					std::string str(buffer);
					this->launch_cmd(str, i, &level);
				}
				// if regarder l'event deconnection quand on a pas de quit on envoie un quit 
			}
		}
	}
}


/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void Server::launch_cmd(std::string msg, int index, int *level)
{ 
	if (msg.find("PASS") != std::string::npos && *level == 0)
	{
		if (!isRightPassword(msg))
			close(_lst_fd[index]);
	}
	//PASS
	/*comparer pass level 0
	si ce n'est pas bon on le deconnecte 
	close le fd trouver la socket du user pour deconnecter 
	_lst_fd; trouver le bon fd[index]
	*/
	//level 1 nick 
	//level 2 user 
	else if (msg.find("NICK") != std::string::npos)
		this->add_user(msg);
	//USER
	
	/*
		/exit = QUIT 

	*/
	else if (msg.find("QUIT") != std::string::npos) 
		this->_lst_fd.erase(this->_lst_fd.begin() + index);
	else if (msg.find("JOIN") != std::string::npos)
		this->join(msg, index);
	else if (msg.find("PRIVMSG") != std::string::npos)
		this->privmsg(msg, index);
	else if (msg.find("INVITE") != std::string::npos)
		this->invite(msg, index);
}


/*void Server::_closeCurrentUser(int currentIndex)
{
	for (size_t i = 0; i < this->_pollFD.size(); i++)
	{
		if (this->_pollFD[i].fd == currentIndex) {
			this->_pollFD.erase(this->_pollFD.begin() + i);
			break;
		}
	}

	// Delete user's presence in all channels
	for (size_t i = 0; i < this->_users[currentIndex]->getChannels().size(); i++)
	{
		this->_users[currentIndex]->getChannels()[i]->removeUser(this->_users[currentIndex]);
	
		// Resend to all channels the list of users
		this->_users[currentIndex]->getChannels()[i]->sendUsersList();
	}
	this->_users[currentIndex]->clearChannels();

	delete (this->_users[currentIndex]);
	this->_users.erase(currentIndex);
	close(currentIndex);
}*/


void Server::create_user()
{
	struct sockaddr_in cli_addr;
	socklen_t clilen;

	std::cout << "Create User : " << std::endl;
	clilen = sizeof(struct sockaddr_in);
	int newsockfd = accept(this->_socketfd, (struct sockaddr *) &cli_addr, &clilen);
	std::cout << "fd : " << newsockfd << std::endl;
	struct pollfd new_socket_fd;
	new_socket_fd.fd = newsockfd;
	new_socket_fd.events = POLLIN;
	this->_lst_fd.push_back(new_socket_fd);
}

/*- - - - - - - - - - - - - - - - - PASS - - - - - - - - - - - -- - -  - - */


bool Server::isRightPassword(std::string msg)
{
	std::istringstream	iss(msg);
	std::string			line;
	std::string			password;
	while (std::getline(iss, line)) 
	{
		size_t pos = line.find("PASS");
		if (pos != std::string::npos) {
			password = line.substr(5);
			password = password.substr(0, password.size() - 1);
			std::cout << BLUE << "PASSWORD = " << password << RESET << std::endl;
		}
	}
	if (password != this->_password)
	{
		std::cout << RED << "[ERROR] wrong password" << RESET << std::endl;
		return (false);
	}
	return (true);
}


/*- - - - - - - - - - - - - - - - - Instanciate user class - - - - - - - - - - - -- - -  - - */

void Server::add_user(std::string msg)
{
	std::string 	nickname;
	std::string 	username;
	
	nickname = getNickname(msg);
	username = getUsername(msg);
	User user(nickname, username, this->_lst_fd[this->_lst_fd.size() - 1].fd, false);
	for (std::vector<User>::const_iterator it = _lst_usr.begin(); it != _lst_usr.end(); ++it) 
	{
		if (it->getNickname() == nickname && it->getIsCreate() == true)
		{
			//change error msg
			std::cout << RED << "[ERROR]" << nickname << " already exist" << RESET << std::endl;
			std::cout << GREEN << "Enter another Nickname" << RESET << std::endl;
			return ;
		}
		it->getNickname();
	}
   	this->_lst_usr.push_back(user);
	this->_lst_usr.back().setIsCreate(true);
	return ;
}

std::string Server::getNickname(std::string msg)
{
	std::istringstream	iss(msg);
	std::string			line;
	std::string			nickname;

	while (std::getline(iss, line)) 
	{
		size_t pos = line.find("NICK");
		if (pos != std::string::npos) {
			nickname = line.substr(5);
			nickname = nickname.substr(0, nickname.size() - 1);
		}
	}
	/*std::string	array[6] = {"PASS", "NICK", "USER", "JOIN", "KICK", "TOPIC"};
	for (int i = 0; i < 6; i++)
	{
		if (array[i] == nickname)
			throw ambiguousNickname();
	}*/
	return (nickname);
}
std::string Server::getUsername(std::string msg)
{
	size_t				end = 0;
	std::istringstream	iss(msg);
	std::string			line;
	std::string			username;

	while (std::getline(iss, line)) 
	{
		size_t index = line.find("USER");
		if (index != std::string::npos) 
		{
			for (size_t i = 5; i < line.size(); i++){
				if (line[i] == ' ')
				{
					end = i;
					break ;
				}
			}
			username = line.substr(5,end - 5);
		}
	}
	return (username);
}

/*
creat une function lors de la deconnection du client qui va supprimer 
du vecteur user 
de la map channel 
std::map<User, int>	_lstUsers;
std::vector<User>	_vecUsers;
*/