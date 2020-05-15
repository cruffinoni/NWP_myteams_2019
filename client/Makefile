##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##

MAIN_FILE			=	./src/main.c

INCLUDE_PATH		=	./include/
INCLUDE_SHARED_PATH	=	../shared

UTILS				=	$(INCLUDE_SHARED_PATH)/utils/str_to_array_ex.c	\
						$(INCLUDE_SHARED_PATH)/utils/tab.c				\
						$(INCLUDE_SHARED_PATH)/utils/string.c			\

SRC					=	src/socket.c						\
						src/client/parse_user_entry.c		\
						src/client/shell.c					\
						src/client/process_commands.c		\
						src/client/commands/help.c			\
						src/client/commands/login.c			\
						src/client/commands/logout.c		\
						src/client/get_server_response.c	\

ALL_SRC				=	$(SRC) $(UTILS)

NAME				=	myteams_cli

SRC_TEST			=	./tests/test.c
NAME_TEST			=	test_server

CFLAGS				=	-Wall -Wextra -I $(INCLUDE_PATH) -I $(INCLUDE_SHARED_PATH)

OBJ					=	$(ALL_SRC:.c=.o)
OBJ_MAIN			=	$(MAIN_FILE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CFLAGS)

debug:
	gcc -o $(NAME) $(ALL_SRC) $(MAIN_FILE) $(CFLAGS) -g

tests_run: all
	gcc $(CFLAGS) $(SRC_TEST) -o test_nm

clean:
	@rm -f $(OBJ) $(OBJ_MAIN)

fclean:
	@rm -f $(OBJ) $(OBJ_MAIN)
	@rm -f $(NAME) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re debug
