##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##

MAIN_FILE		=	./src/main.c

INCLUDE_PATH		=	./include/
INCLUDE_SHARED_PATH	=	../shared

SRC_UTILS		=	$(INCLUDE_SHARED_PATH)/utils/str_to_array_ex.c	\
					$(INCLUDE_SHARED_PATH)/utils/tab.c

SRC_SERVER		=	./src/server/management.c	\
					./src/server/socket.c		\
					./src/server/connection.c

SRC_CLIENT		=	./src/client/management.c	\

SRC				=	./src/error/error.c			\

ALL_SRC			=	$(SRC) $(SRC_SERVER) $(SRC_CLIENT) $(SRC_UTILS)

NAME			=	myteams_server

SRC_TEST		=	./tests/test.c
NAME_TEST		=	test_server


CFLAGS			=	-Wall -Wextra -I $(INCLUDE_PATH) -I $(INCLUDE_SHARED_PATH)

OBJ				=	$(ALL_SRC:.c=.o)
OBJ_MAIN		=	$(MAIN_FILE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CFLAGS)

debug:
	gcc -o $(NAME) $(ALL_SRC) $(MAIN_FILE) $(CFLAGS) -g

tests_run: all
	gcc $(CFLAGS) $(SRC_TEST) -o $(NAME_TEST)

clean:
	@rm -f $(OBJ) $(OBJ_MAIN)

fclean:
	@rm -f $(OBJ) $(OBJ_MAIN)
	@rm -f $(NAME) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re debug
