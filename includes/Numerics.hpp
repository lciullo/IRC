#ifndef NUMERIC_HPP
# define NUMERIC_HPP

#include "Server.hpp"

void	send_msg(User user, std::string msg);

# define RN + "\r\n"
# define SPACE + " "
# define IP_ADDR "localhost"

# define HEADER_CMD(User) \
(!User.getNickname().empty() ? ":" + User.getNickname() + "!" + User.getUsername() + " " : ":unknown ")

//001 - SIMPLE_MSG
# define SIMPLE_MSG(user, msg) \
send_msg(user, HEADER_CMD(user) + "001 " + user.getNickname() + SPACE + ":" + msg + RN)

//324 - RPL_CHANNELMODEIS
# define RPL_CHANNELMODEIS(user, channel_name, modestring) \
send_msg(user, HEADER_CMD(user) + "324 " + user.getNickname() + SPACE + channel_name + SPACE + modestring + RN)

//329 - RPL_CREATIONTIME
#define RPL_CREATIONTIME(user, channel_name, creation_time) \
send_msg(user, HEADER_CMD(user) + "329 " + user.getNickname() + SPACE + channel_name + SPACE + creation_time + RN)

//331 - RPL_NOTOPIC
# define RPL_NOTOPIC(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "331 " + user.getNickname() + SPACE + channel_name + SPACE + ":No topic is set" + RN)

//332 - RPL_TOPIC
# define RPL_TOPIC(user, channel_name, channel_topic) \
send_msg(user, HEADER_CMD(user) + "332 " + user.getNickname() + SPACE + channel_name + SPACE  + ":" + channel_topic + RN)

//333 - RPL_TOPICWHOTIME
# define RPL_TOPICWHOTIME(user, channel_name, topic_info) \
send_msg(user, HEADER_CMD(user) + "333 " + user.getNickname() + SPACE + channel_name + SPACE + topic_info + RN)

//336 - RPL_INVITELIST
# define RPL_INVITELIST(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "336 " + user.getNickname() SPACE + channel_name + RN)

//341 - RPL_INVITING
# define RPL_INVITING(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "341 " + user.getNickname() SPACE + nick SPACE + channel_name RN)

//401 - ERR_NOSUCHNICK
# define ERR_NOSUCHNICK(user, nickname) \
send_msg(user, HEADER_CMD(user) + "401 " + user.getNickname() + SPACE + nickname + SPACE + ":No such nick/channel" + RN)

//403 - ERR_NOSUCHCHANNEL
# define ERR_NOSUCHCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "403 " + user.getNickname() + SPACE + channel_name + SPACE + ":No such channel" + RN)

//404 - ERR_CANNOTSENDTOCHAN
# define ERR_CANNOTSENDTOCHAN(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "404 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot send to channel" + RN)

//412 - ERR_NOTEXTTOSEND
# define ERR_NOTEXTTOSEND(user) \
send_msg(user, HEADER_CMD(user) + "412 " + user.getNickname() + SPACE + ":No text to send (put ':' before text)" + RN)

//421 - ERR_UNKNOWNCOMMAND
# define ERR_UNKNOWNCOMMAND(user, command) \
send_msg(user, HEADER_CMD(user) + "421 " + user.getNickname() + SPACE + command + SPACE + ":Unknown command" + RN)

//431 - ERR_NONICKNAMEGIVEN
# define ERR_NONICKNAMEGIVEN(user, nickname) \
send_msg(user, HEADER_CMD(user) + "431 " + user.getNickname() + SPACE + nickname + SPACE + "No nickname given" + RN)

//432 - ERR_ERRONEUSNICKNAME
# define ERR_ERRONEUSNICKNAME(user, nickname) \
send_msg(user, HEADER_CMD(user) + "432 " + user.getNickname() + SPACE + nickname + SPACE + "Erroneus nickname" + RN)

//433 - ERR_NICKNAMEINUSE
# define ERR_NICKNAMEINUSE(user, nickname) \
send_msg(user, HEADER_CMD(user) + "433 " + (!user.getNickname().empty() ? user.getNickname() : "unknown") + SPACE + nickname + SPACE + ":Nickname is already in use" + RN)

//441 - ERR_USERNOTINCHANNEL
# define ERR_USERNOTINCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "441 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":They aren't on that channel" + RN)

//442 - ERR_NOTONCHANNEL
# define ERR_NOTONCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "442 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not on that channel" + RN)

//443 - ERR_USERONCHANNEL
# define ERR_USERONCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "443 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":is already on channel" + RN)

//451 - ERR_NOTREGISTERED
# define ERR_NOTREGISTERED(user) \
send_msg(user, HEADER_CMD(user) + "451 " + (!user.getNickname().empty() ? user.getNickname() : "unknown") + SPACE + ":You have not registered" + RN)

//461 - ERR_NEEDMOREPARAMS
# define ERR_NEEDMOREPARAMS(user, cmd) \
send_msg(user, HEADER_CMD(user) + "461 " + user.getNickname() + SPACE + cmd + SPACE + ":Not enough parameters" + RN)

//462 - ERR_ALREADYREGISTERED
# define ERR_ALREADYREGISTERED(user) \
send_msg(user, HEADER_CMD(user) + "462 " + user.getNickname() + SPACE + ":You may not reregister" + RN)

//464 - ERR_PASSWDMISMATCH
# define ERR_PASSWDMISMATCH(user) \
send_msg(user, HEADER_CMD(user) + "464 " + (!user.getNickname().empty() ? user.getNickname() : "unknown") + SPACE + ":Password incorrect" + RN)

//471 - ERR_CHANNELISFULL
# define ERR_CHANNELISFULL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "471 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, channel is full" + RN)

//472 - ERR_UNKNOWNMODE
# define ERR_UNKNOWNMODE(user, modechar) \
send_msg(user, HEADER_CMD(user) + "472 " + user.getNickname() + SPACE + modechar + SPACE + ":is unkown mode char to me" + RN)

//473 - ERR_INVITEONLYCHAN
# define ERR_INVITEONLYCHAN(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "473 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, invite only" + RN)

//475 - ERR_BADCHANNELKEY
# define ERR_BADCHANNELKEY(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "475 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, wrong key" + RN)

//476 - ERR_BADCHANMASK
# define ERR_BADCHANMASK(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "476 " + channel_name + SPACE + "Bad Channel Mask" + RN)

//482 - ERR_CHANOPRIVSNEEDED
# define ERR_CHANOPRIVSNEEDED(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "482 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not channel operator" + RN)

//696 - ERR_INVALIDMODEPARAM
# define ERR_INVALIDMODEPARAM(user, channel_name, modechar, parameter, description) \
send_msg(user, HEADER_CMD(user) + "696 " + user.getNickname() + channel_name + SPACE + modechar + SPACE + "\'" + parameter + "\'" + SPACE + ":" + description + RN)

//Send to server new nickname 
# define RPL_NICK(nickname, username, newNickname) (":" + nickname + "!" + username + "@localhost NICK " +  newNickname + RN)

# define INVITE_MESSAGE(user, channel_name, nick) \
send_msg(*user, HEADER_CMD(client) + "INVITE " + user->getNickname() + SPACE + channel_name RN)

# define KICK_WITHOUT_REASON(user, kicker, channel_name, nick) \
send_msg(user, HEADER_CMD(kicker) + "KICK " +  channel_name + SPACE + nick + RN)

# define KICK_WITH_REASON(user, kicker, channel_name, nick, reason) \
send_msg(user, HEADER_CMD(kicker) + "KICK " +  channel_name + SPACE + nick + SPACE + reason + RN)

# define MODE_MESSAGE(user, client, channel_name, modestring) \
send_msg(user, HEADER_CMD(client) + "MODE " +  channel_name + SPACE + modestring + RN)

# define NOTICE(user, channel_name, msg) \
send_msg(user, HEADER_CMD(user) + "NOTICE " +  channel_name + SPACE + msg + RN)

#endif