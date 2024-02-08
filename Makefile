# ====================== VARIABLES ====================== #

# --- Executable ---

NAME			=	ircserv

# --- Debug ---

DEBUG			=	no

VALGRIND		=	no

# --- Command ---

RM				=	rm -rf

# --- Directories ---

DIR_DEP			=	.dep/

DIR_SRCS 		=	sources/

DIR_INC			=	includes/

# ====================== PATHS ====================== #

# --- List ---

SRCS			=	${DIR_SRCS}main.cpp \
					${DIR_SRCS}Server.cpp \
					${DIR_SRCS}User.cpp \
					${DIR_SRCS}Channel.cpp \
					${DIR_SRCS}utils.cpp \
					${DIR_SRCS}commands/pass.cpp \
					${DIR_SRCS}commands/nick.cpp \
					${DIR_SRCS}commands/user.cpp \
					${DIR_SRCS}commands/invite.cpp \
					${DIR_SRCS}commands/kick.cpp \
					${DIR_SRCS}commands/mode.cpp \
					${DIR_SRCS}commands/topic.cpp \
					${DIR_SRCS}commands/join.cpp \
					${DIR_SRCS}commands/part.cpp \
					${DIR_SRCS}commands/quit.cpp \
					${DIR_SRCS}commands/utils_quit.cpp \
					${DIR_SRCS}commands/privmsg.cpp
					
				

INC				=	${DIR_INC}IRC.hpp \
					${DIR_INC}Server.hpp \
					${DIR_INC}User.hpp \
					${DIR_INC}Channel.hpp \
					${DIR_INC}Numerics.hpp

				
# --- Paths ---

OBJ				=	${patsubst %.cpp, ${DIR_DEP}%.o, ${SRCS}}

DEP				=	${patsubst %.cpp, ${DIR_DEP}%.d, ${SRCS}}
				 
# ====================== FLAGS ====================== #

# ---- Cpp ---- #

FLAGS			=	-Wall -Wextra -Werror -g3 -I ${DIR_INC}

CPP				=	c++ -std=c++98

# ---- Dep ---- #

DEP_FLAGS		=	-MMD -MP

# ---- Debug ---- #

DFLAGS			= -g3 -fsanitize=address

ifeq (${DEBUG}, yes)
 FLAGS		+= ${DFLAGS}
endif

LEAKS			=	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --quiet

# ====================== RULES ====================== #

# ---- Compilation ---- #

all:			${NAME}

${NAME}:		${OBJ}
				${CPP} ${FLAGS} -o ${NAME} ${OBJ}

-include ${DEP}

${DIR_DEP}%.o: %.cpp
				@mkdir -p $(shell dirname $@)
				${CPP} ${FLAGS} ${DEP_FLAGS} -c $< -o $@

# ---- Debug ---- #

debug:
	${MAKE} -j re DEBUG=yes

leaks:
	clear
	${MAKE} -j VALGRIND=yes
	${LEAKS} ./ircserv 6969 test

# ---- Clean ---- #

clean:
				${RM} ${DIR_DEP}

fclean: clean
				${RM} ${NAME}

re:				fclean
				${MAKE} all

.PHONY :		all clean fclean re