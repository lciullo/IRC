#ifndef IRC_HPP
#define IRC_HPP

//======== LIBRAIRIES ==========//

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

//======== DEFINE =============//

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

using	std::cout;
using	std::endl;

//======== INCLUDES ==========//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>


#endif 