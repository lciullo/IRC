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
send_msg(user, HEADER_CMD(user) + "401 " + user.getNickname() + SPACE + nickname + SPACE + ":No such nick/channel" + RN)

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

# define RPL_NICK(nickname, username, newNickname) (":" + nickname + "!" + username + "@localhost NICK " +  newNickname + RN)

# define ERR_BADCHANMASK(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "476 " + channel_name + SPACE + ":Bad Channel Mask" + RN)

# define ERR_BADCHANNELKEY(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "475 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, wrong key" + RN)

# define ERR_INVITEONLYCHAN(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "473 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, invite only" + RN)

# define ERR_CHANNELISFULL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "471 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, channel is full" + RN)

# define RPL_TOPIC(user, channel_name, channel_topic) \
send_msg(user, HEADER_CMD(user) + "332 " + user.getNickname() + SPACE + channel_name + SPACE + ":" + channel_topic + RN)

# define ERR_CHANOPRIVSNEEDED(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "482 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not channel operator" + RN)

# define ERR_USERONCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "443 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":is already on channel" + RN)

# define RPL_INVITING(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "341 " + user.getNickname() SPACE + nick SPACE + channel_name RN)

# define RPL_CHANNELMODEIS(user, channel_name, modestring) \
send_msg(user, HEADER_CMD(user) + "324 " + user.getNickname() + SPACE + channel_name + SPACE + modestring + RN)

#define RPL_CREATIONTIME(user, channel_name, creation_time) \
send_msg(user, HEADER_CMD(user) + "329 " + user.getNickname() + SPACE + channel_name + SPACE + creation_time + RN)

# define RPL_NOTOPIC(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "331 " + user.getNickname() + SPACE + channel_name + SPACE + ":No topic is set" + RN)

# define RPL_TOPICWHOTIME(user, channel_name, topic_info) \
send_msg(user, HEADER_CMD(user) + "333 " + user.getNickname() + SPACE + channel_name + SPACE + topic_info + RN)

# define RPL_INVITELIST(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "336 " + user.getNickname() SPACE + channel_name + RN)

# define ERR_USERNOTINCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "441 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":They aren't on that channel" + RN)

# define ERR_UNKNOWNMODE(user, modechar) \
send_msg(user, HEADER_CMD(user) + "472 " + user.getNickname() + SPACE + modechar + SPACE + ":is unkown mode char to me" + RN)

# define ERR_INVALIDMODEPARAM(user, channel_name, modechar, parameter, description) \
send_msg(user, HEADER_CMD(user) + "696 " + user.getNickname() + channel_name + SPACE + modechar + SPACE + "\'" + parameter + "\'" + SPACE + ":" + description + RN)

# define INVITE_MESSAGE(user, channel_name, nick) \
send_msg(*user, ":" + user->getNickname() + "!" + user->getUsername() SPACE + "INVITE " + nick SPACE + channel_name RN)

# define KICK_WITHOUT_REASON(user, kicker, channel_name, nick) \
send_msg(user, HEADER_CMD(kicker) + "KICK " +  channel_name + SPACE + nick + RN)

# define KICK_WITH_REASON(user, kicker, channel_name, nick, reason) \
send_msg(user, HEADER_CMD(kicker) + "KICK " +  channel_name + SPACE + nick + SPACE + reason + RN)

#endif