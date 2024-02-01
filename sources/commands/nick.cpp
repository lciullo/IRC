#include "Server.hpp"

std::string Server::getNickname(std::string msg)
{
	std::istringstream	iss(msg);
	std::string			line;
	std::string			nickname;

	/*User &user = GetUserByFd(fd);
	std::vector<std::string> cmd;

	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "PART");
		return ;
	}*/
	while (std::getline(iss, line)) 
	{
		size_t pos = line.find("NICK");
		if (pos != std::string::npos) {
			nickname = line.substr(5);
			nickname = nickname.substr(0, nickname.size());
		}
	}
	
	return (nickname);
}


bool Server::nick(std::string msg, std::string nickname, int fd)
{
	User &user = GetUserByFd(fd);
	std::vector<std::string> cmd;

	split_cmd(&cmd, msg);
	if (cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(user, "PART");
		return (false);
	}
	std::string toUpdate;
	std::string secondChoice = user.getSecondChoice();
	if (nickname.empty())
	{
		ERR_NONICKNAMEGIVEN(this->GetUserByFd(fd), nickname);
		return (false);
	}
	std::vector<std::string> cmdLst = getCmdLst();
	for (std::vector<std::string>::iterator it = cmdLst.begin(); it != cmdLst.end(); ++it) 
	{
		if (*it == nickname)
		{
			ERR_ERRONEUSNICKNAME(this->GetUserByFd(fd), nickname);
			return (false);
		}
	}
	std::map<int, User>::iterator ite = this->_lst_usr.end();
	for (std::map<int, User>::iterator it = this->_lst_usr.begin(); ite != it; ++it)
	{
		if (it->second.getNickname() == nickname)
		{
			ERR_NICKNAMEINUSE(this->GetUserByFd(fd), nickname);
			if (secondChoice.empty())
				user.setSecondChoice(nickname);
			return (false);
		}
	}
	if (secondChoice.empty())
		toUpdate = nickname;
	else
		toUpdate = secondChoice;
	user.setNickname(toUpdate);
	sendStringSocket(fd, RPL_NICK(toUpdate, user.getUsername(), nickname));
	user.setSecondChoice(nickname);
	std::cout << BLUE << "second choice = " << secondChoice << std::endl;
	std::cout << BLUE << "toUpdate = " << toUpdate << std::endl;
	return (true);
}

std::vector<std::string> Server::getCmdLst(void)
{
	std::vector<std::string> cmdLst;
	cmdLst.push_back("NICK");
	cmdLst.push_back("nick");
	cmdLst.push_back("INVITE");
	cmdLst.push_back("invite");
	cmdLst.push_back("JOIN");
	cmdLst.push_back("join");
	cmdLst.push_back("PART");
	cmdLst.push_back("part");
	cmdLst.push_back("PASS");
	cmdLst.push_back("pass");
	cmdLst.push_back("PRIVMSG");
	cmdLst.push_back("privmsg");
	cmdLst.push_back("QUIT");
	cmdLst.push_back("quit");
	cmdLst.push_back("TOPIC");
	cmdLst.push_back("topic");
	cmdLst.push_back("USER");
	cmdLst.push_back("user");
	cmdLst.push_back("\r");
	cmdLst.push_back("\n");
	cmdLst.push_back("\t");
	cmdLst.push_back("\v");
	cmdLst.push_back(":");
	cmdLst.push_back("#");
	cmdLst.push_back("&");
	cmdLst.push_back(" ");
	return (cmdLst);
}