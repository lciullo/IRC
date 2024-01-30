#ifndef NUMERIC_HPP
# define NUMERIC_HPP

#include "Server.hpp"

void	send_msg(User user, std::string msg);

# define RN + "\r\n"
# define SPACE + " "
# define IP_ADDR "localhost"

# define HEADER_CMD(User) \
":" + User.getNickname() + "!" + User.getUsername() + " "

# define ERR_NEEDMOREPARAMS(user, cmd) \
send_msg(user, HEADER_CMD(user) + "461 " + user.getNickname() + SPACE + cmd + SPACE + ":Not enough parameters" + RN)

# define ERR_NOTONCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "442 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not on that channel" + RN)

# define ERR_NOSUCHCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "403 " + user.getNickname() + SPACE + channel_name + SPACE + ":No such channel" + RN)

//======= NICK =======//

//Empty Nickname : 431

# define ERR_NONICKNAMEGIVEN(user, nickname) \
send_msg(user, HEADER_CMD(user) + "431 " + user.getNickname() + SPACE + nickname + SPACE + ":No nickname given" + RN)

//Characters disallowed by the server : 432

# define ERR_ERRONEUSNICKNAME(user, nickname) \
send_msg(user, HEADER_CMD(user) + "432 " + user.getNickname() + SPACE + nickname + SPACE + ":Erroneus nickname" + RN)

//Nickname already use : 433

# define ERR_NICKNAMEINUSE(user, nickname) \
send_msg(user, HEADER_CMD(user) + "433 " + user.getNickname() + SPACE + nickname + SPACE + ":Nickname is already in use" + RN)

//Send to server new nickname 

# define RPL_NICK(nickname, username, newNickname) (":" + nickname + "!" + username + "@localhost NICK " +  newNickname + "\r\n")

#endif