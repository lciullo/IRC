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

SRCS			=	${DIR_SRCS}main.cpp 
					
				

INC				=	${DIR_INC}IRC.hpp \
					${DIR_INC}Lisa.hpp \
					${DIR_INC}Clemence.hpp \
					${DIR_INC}Aymeric.hpp 	
				
# --- Paths ---

OBJ				=	${patsubst %.cpp, ${DIR_DEP}%.o, ${SRCS}}

DEP				=	${patsubst %.cpp, ${DIR_DEP}%.d, ${SRCS}}
				 
# ====================== FLAGS ====================== #

# ---- Cpp ---- #

FLAGS			=	-Wall -Wextra -Werror -I ${DIR_INC}

CPP				=	c++ -std=c++98

# ---- Dep ---- #

DEP_FLAGS		=	-MMD -MP

# ---- Debug ---- #

DFLAGS			= -g3 -fsanitize=address

ifeq (${DEBUG}, yes)
 FLAGS		+= ${DFLAGS}
endif

# ---- Leaks ---- #

LEAKS			=	valgrind --leak-check=full --show-leak-kinds=all --quiet


# ====================== RULES ====================== #

# ---- Compilation ---- #

all:			${NAME}

${NAME}:		${OBJ}
				${CPP} ${FLAGS} -o ${NAME} ${OBJ}

-include ${DEP}

${DIR_DEP}%.o: %.cpp
				mkdir -p $(shell dirname $@)
				${CPP} ${FLAGS} ${DEP_FLAGS} -c $< -o $@

# ---- Debug ---- #

debug:
	${MAKE} -j re DEBUG=yes

leaks:
	clear
	${MAKE} -j VALGRIND=yes
	${LEAKS} ./ircserv

# ---- Clean ---- #

clean:
				${RM} ${DIR_DEP}

fclean: clean
				${RM} ${NAME}

re:				fclean
				${MAKE} all

.PHONY :		all clean fclean re