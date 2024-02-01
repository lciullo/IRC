#ifndef NUMERIC_HPP
# define NUMERIC_HPP

#include "Server.hpp"

void	send_msg(User user, std::string msg);

# define RN + "\r\n"
# define SPACE + " "


# define HEADER_CMD(User) \
":" + User.getNickname() + "!" + User.getUsername() + " "

# define ERR_NEEDMOREPARAMS(user, cmd) \
send_msg(user, HEADER_CMD(user) + "461 " + user.getNickname() + SPACE + cmd + SPACE + ":Not enough parameters" + RN)

# define ERR_NOTONCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "442 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not on that channel" + RN)

# define ERR_NOSUCHCHANNEL(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "403 " + user.getNickname() + SPACE + channel_name + SPACE + ":No such channel" + RN)

# define ERR_BADCHANMASK(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "476 " + channel_name + SPACE + ":Bad Channel Mask" + RN)

# define ERR_BADCHANNELKEY(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "475 " + user.getNickname() + SPACE + channel_name + SPACE + ":Cannot join channel, wrong key" + RN)

# define ERR_CHANOPRIVSNEEDED(user, channel_name) \
send_msg(user, HEADER_CMD(user) + "482 " + user.getNickname() + SPACE + channel_name + SPACE + ":You're not channel operator" + RN);

# define ERR_USERONCHANNEL(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "443 " + user.getNickname() + SPACE + nick + SPACE + channel_name + SPACE + ":is already on channel" + RN);

# define RPL_INVITING(user, channel_name, nick) \
send_msg(user, HEADER_CMD(user) + "341 " + user.getNickname() + SPACE + nick + SPACE + channel_name + RN);

# define INVITE_MESSAGE(user, channel_name) \
send_msg(*user, ":" + user->getNickname() + "!" + user->getUsername() + " " + "INVITE" + user->getNickname() + SPACE + channel_name + RN);

#endif