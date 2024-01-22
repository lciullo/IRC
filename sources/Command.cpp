
#include "Server.hpp"

void Server::join(std::string msg, int index)
{
	User user = this->_lst_usr[index - 1];
	int i = msg.find("JOIN");
	std::string channel_name = msg.substr(i + 5);
	channel_name = channel_name.substr(0, channel_name.size() - 2); //for remove last \r\n
	if (channel_name[0] != '#')
	{  
		std::string err_msg = HEADER_CMD(user) + "403 " + user.getNickname() + " " + channel_name + " :Put an # before channel name\r\n";
		send(this->_lst_fd[index].fd, err_msg.c_str(), err_msg.size(), 0);
		return ;
	}
	std::map<std::string , Channel>::iterator it;
	it = this->_lst_channel.find(channel_name);
	if (it == this->_lst_channel.end())
	{
		Channel new_channel(channel_name, user);
		std::cout << "create channel " << new_channel.getName() << " by " << user.getNickname() << std::endl;
		//this->_lst_channel[channel_name] = new_channel;
		this->_lst_channel.insert(it, std::pair<std::string, Channel>(channel_name,new_channel)); 
	}
	else
	{
		it->second.addUser(user);
	}
	//Channel channel = it->second;
	std::string message = ":";
	message.append(user.getNickname());
	message.append(" JOIN ");
	message.append(channel_name);
	message.append("\n");
	//std::cout << "message : " << message << std::endl;
	send(this->_lst_fd[index].fd, message.c_str(), message.size(), 0);
	//std::cout << this->_lst_channel[channel_name].getName() << std::endl;
	message = HEADER_CMD(user) + "353 " + user.getNickname() + " = " + channel_name + " :dark\r\n"; // is just a test
	send(this->_lst_fd[index].fd, message.c_str(), message.size(), 0);
	message = HEADER_CMD(user) + "366 " + user.getNickname() + " " + channel_name + " :End of /NAMES list\r\n";
}


void Server::privmsg(std::string msg, int index)
{
	int i = msg.find("PRIVMSG");
	std::string dest = msg.substr(i + 8);
	std::string send_msg = msg.substr(msg.find(":"));
	send_msg = send_msg.substr(0, send_msg.size() - 2); //for remove last \r\n
	i = dest.find(" ");
	dest = dest.substr(0, i);
	std::cout << "dest : " << dest << std::endl;
	if (dest[0] == '#')
	{
		//Channel channel = this->_lst_channel[dest]; //CA MARCHE PAS POUR RECUP LE CHANNEL SELON SON NOM JE SAIS PAS POURQUOI
		std::map<std::string , Channel>::iterator it;
		it = this->_lst_channel.find(dest);
		Channel channel = it->second;
		for (size_t i = 0; i < channel.getLstUsers().size(); i++)
		{
			User user = channel.getLstUsers()[i];
			std::string message = ":" + this->_lst_usr[index - 1].getNickname() + " PRIVMSG " + dest + " " + send_msg + "\n"; //
			std::cout << "message : " << message << std::endl;                                                                // SI JE DECALLE CES DEUX LIGNE EN DESSOUS DU IF CA NE MARCHE PLUS BRESSOM                
			if (user.getNickname() == this->_lst_usr[index - 1].getNickname())
				continue ;
			send(user.getFd(), message.c_str(), message.size(), 0);
		}
	}
}