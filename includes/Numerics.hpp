#ifndef NUMERIC_HPP
# define NUMERIC_HPP

#include "Server.hpp"

void	send_msg(User user, std::string msg);

# define RN + "\r\n"
# define SPACE + " "


# define ERR_NEEDMOREPARAMS(client, cmd) \
send_msg(client, client.getNickname() SPACE + cmd SPACE + ":Not enough parameters" RN)

#endif