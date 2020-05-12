##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##

MAIN_FILE		=	./src/main.c

SRC				=	./src/error/error.c			\
					./src/server/management.c	\
					./src/server/socket.c

ALL_SRC			= $(SRC)

NAME			=	myteams_server

SRC_TEST		=	./tests/test.c
NAME_TEST		=	test_server

INCLUDE_PATH	=	./include/

CFLAGS			=	-Wall -Wextra -I $(INCLUDE_PATH)

OBJ				=	$(ALL_SRC:.c=.o)
OBJ_MAIN		=	$(MAIN_FILE:.c=.o)

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
