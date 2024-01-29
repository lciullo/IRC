#include "Server.hpp"

void sendUserList(Channel channel)
{
	std::string message;

	for (size_t i = 0; i < channel.getVecUsers().size(); i++)
	{
		User &user2 = *channel.getVecUsers()[i];
		for (size_t j = 0; j < channel.getVecUsers().size(); j++)
		{
			User userToSend = *channel.getVecUsers()[j];
			message = HEADER_CMD(userToSend) + "353 " + userToSend.getNickname() + " = " + channel.getName() + " :";
			if (channel.getLstUsers()[&user2] == OPERATOR)
				message.append("@");
			else if (channel.getLstUsers()[&user2] == VOICE)
				message.append("+");
			message.append(user2.getNickname() + "\r\n");
			send(userToSend.getFd(), message.c_str(), message.size(), 0);
		}
	}
	for (size_t j = 0; j < channel.getVecUsers().size(); j++)
	{
		User userToSend = *channel.getVecUsers()[j];
		message = HEADER_CMD(userToSend) + "366 " + userToSend.getNickname() + " " + channel.getName() + " :End of /NAMES list\r\n";
		send(channel.getVecUsers()[j]->getFd(), message.c_str(), message.size(), 0);
	}
}

void Server::join(std::string msg, int fd)
{
	std::cout << "[CMD] JOIN" << std::endl; 
	User &user = this->GetUserByFd(fd);
	int i = msg.find("JOIN");
	std::string channel_name = msg.substr(i + 5);
	channel_name = channel_name.substr(0, channel_name.size());
	if (channel_name[0] != '#' && channel_name[0] != '&')
	{  
		std::string err_msg = HEADER_CMD(user) + "403 " + user.getNickname() + " " + channel_name + " :Put an # before channel name\r\n";
		send(fd, err_msg.c_str(), err_msg.size(), 0);
		return ;
	}
	std::map<std::string , Channel>::iterator it;
	it = this->_lst_channel.find(channel_name);
	if (it == this->_lst_channel.end())
	{
		Channel new_channel(channel_name, &user);
		std::cout << "create channel " << new_channel.getName() << " by " << user.getNickname() << std::endl;
		this->_lst_channel[channel_name] = new_channel;
	}
	else
		it->second.addUser(&user);
	Channel channel = this->_lst_channel[channel_name];
	std::string message = HEADER_CMD(user) + "JOIN " + channel_name + "\r\n";
	send(fd, message.c_str(), message.size(), 0);
	sendUserList(channel);
}