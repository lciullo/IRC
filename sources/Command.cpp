
#include "Server.hpp"

void sendUserList(Channel channel, User user)
{
	std::string message;

	for (size_t i = 0; i < channel.getLstUsers().size(); i++)
	{
		//for (size_t j = 0; j < channel.getLstUsers().size(); j++)
		//{
			User userToSend = *channel.getLstUsers()[i];
			std::cout << userToSend.getNickname() << std::endl;
			message = HEADER_CMD(userToSend) + "353 " + user.getNickname() + " = " + channel.getName() + " :";
			if (channel.getMapUsers()[&user] == OPERATOR)
				message.append("@");
			else
				message.append("+");
			message.append(user.getNickname() + "\r\n");
			std::cout << "message : " << message << std::endl;
			send(channel.getLstUsers()[i]->getFd(), message.c_str(), message.size(), 0);
		//}
	}
	for (size_t j = 0; j < channel.getLstUsers().size(); j++)
	{
		User userToSend = *channel.getLstUsers()[j];
		message = HEADER_CMD(userToSend) + "366 " + userToSend.getNickname() + " " + channel.getName() + " :End of /NAMES list\r\n";
		send(channel.getLstUsers()[j]->getFd(), message.c_str(), message.size(), 0);
	}
}

User &Server::GetUserByFd(int fd)
{
	std::vector<User>::iterator ite = this->_lst_usr.end();
	for (std::vector<User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->getFd() == fd)
			return (*it);
	}
	return (*ite);
}

void Server::join(std::string msg, int index)
{
	//Channel channel;
	//User &user = this->_lst_usr[index - 1];
	User &user = this->GetUserByFd(this->_lst_fd[index].fd);
	int i = msg.find("JOIN");
	std::string channel_name = msg.substr(i + 5);
	channel_name = channel_name.substr(0, channel_name.size() - 2); //for remove last \r\n
	if (channel_name[0] != '#' && channel_name[0] != '&')
	{  
		std::string err_msg = HEADER_CMD(user) + "403 " + user.getNickname() + " " + channel_name + " :Put an # before channel name\r\n";
		send(this->_lst_fd[index].fd, err_msg.c_str(), err_msg.size(), 0);
		return ;
	}
	std::map<std::string , Channel>::iterator it;
	it = this->_lst_channel.find(channel_name);
	if (it == this->_lst_channel.end())
	{
		Channel new_channel(channel_name, &user);
		std::cout << "create channel " << new_channel.getName() << " by " << user.getNickname() << std::endl;
		//this->_lst_channel[channel_name] = new_channel;
		this->_lst_channel.insert(it, std::pair<std::string, Channel>(channel_name,new_channel)); 
		//channel = new_channel;
	}
	else
	{
		it->second.addUser(&user);
		//channel = it->second;
	}
	Channel channel = this->_lst_channel[channel_name];
	std::string message = HEADER_CMD(user) + "JOIN " + channel_name + "\r\n";
	//std::cout << "message : " << message << std::endl;
	send(this->_lst_fd[index].fd, message.c_str(), message.size(), 0);
	std::cout << "channel : " << channel.getName() << std::endl;
	sendUserList(channel, user);
}

void Server::privmsg(std::string msg, int index)
{
	int i = msg.find("PRIVMSG");
	std::string dest = msg.substr(i + 8);
	std::string send_msg = msg.substr(msg.find(":"));
	send_msg = send_msg.substr(0, send_msg.size() - 2); //for remove last \r\n
	i = dest.find(" ");
	dest = dest.substr(0, i);
	
	if (dest[0] == '#')
	{
		Channel channel = this->_lst_channel[dest];
		for (size_t i = 0; i < channel.getLstUsers().size(); i++)
		{
			User *user = channel.getLstUsers()[i];
			std::string message = ":" + this->GetUserByFd(this->_lst_fd[index].fd).getNickname() + " PRIVMSG " + dest + " " + send_msg + "\n"; //
			if (user->getNickname() == this->GetUserByFd(this->_lst_fd[index].fd).getNickname())
				continue ;
			send(user->getFd(), message.c_str(), message.size(), 0);
		}
	}
}