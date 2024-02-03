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

# define ERR_NOTEXTTOSEND(user) \
send_msg(user, HEADER_CMD(user) + "412 " + user.getNickname() + SPACE + ":No text to send (put ':' before text)" + RN)

# define ERR_CANNOTSENDTOCHAN(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "404 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot send to channel" + RN)

# define ERR_NOSUCHNICK(user, nickname) \
send_msg(user, HEADER_CMD(user) + "401 " + user.getNickname() + SPACE + nickname + SPACE + ":No such nick" + RN)

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

# define ERR_BADCHANMASK(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "476 " + channel_name + SPACE + ":Bad Channel Mask" + RN)

# define ERR_BADCHANNELKEY(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "475 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, wrong key" + RN)

# define ERR_INVITEONLYCHAN(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "473 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, invite only" + RN)

# define ERR_CHANNELISFULL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "471 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, channel is full" + RN)

# define RPL_TOPIC(user, channel) \
send_msg(user, HEADER_CMD(user) + "332 " + user.getNickname() + SPACE + channel.getName() + SPACE + ":" + channel.getTopic() + RN)

# define ERR_CHANOPRIVSNEEDED(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "482 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not channel operator" + RN);

# define ERR_USERONCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "443 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":is already on channel" + RN);

# define RPL_INVITING(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "341 " + user.getNickname() + SPACE + nick + SPACE + channel_name + RN);

# define INVITE_MESSAGE(user, channel_name) \
send_msg(*user, ":" + user->getNickname() + "!" + user->getUsername() + " " + "INVITE" + user->getNickname() + SPACE + channel_name + RN);

#endif