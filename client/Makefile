##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##

MAIN_FILE			=	./src/main.c

INCLUDE_PATH		=	./include/
INCLUDE_LIB_PATH	=	../libs/
INCLUDE_SHARED_PATH	=	../shared

UTILS				=	$(INCLUDE_SHARED_PATH)/uid.c								\
						$(INCLUDE_SHARED_PATH)/utils/str_to_array_ex.c				\
						$(INCLUDE_SHARED_PATH)/utils/tab.c							\
						$(INCLUDE_SHARED_PATH)/utils/string.c						\

SRC					=	src/socket.c												\
						src/client/parse_user_entry.c								\
						src/client/shell.c											\
						src/client/process_commands.c								\
						src/client/commands/login.c									\
						src/client/commands/logout.c								\
						src/client/commands/list/list.c								\
						src/client/commands/list/list_users.c						\
						src/client/commands/list/list_teams.c						\
						src/client/commands/notifications/notifications.c			\
						src/client/commands/notifications/private_message.c			\
						src/client/commands/forbidden.c								\
						src/client/utils/get_server_response.c						\
						src/client/utils/user_gestion.c								\
						src/client/utils/send_server_message.c						\

ALL_SRC				=	$(SRC) $(UTILS)

NAME				=	myteams_cli

SRC_TEST			=	./tests/test.c
NAME_TEST			=	test_server

LDFLAGS				+=	-l uuid -L ../libs/myteams -l myteams
CFLAGS				+=	-Wall -Wextra -I $(INCLUDE_PATH) -I $(INCLUDE_SHARED_PATH) -I $(INCLUDE_LIB_PATH)

OBJ					=	$(ALL_SRC:.c=.o)
OBJ_MAIN			=	$(MAIN_FILE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CFLAGS) $(LDFLAGS)

debug:
	gcc -o $(NAME) $(ALL_SRC) $(MAIN_FILE) $(CFLAGS) $(LDFLAGS) -g

tests_run: all
	gcc $(CFLAGS) $(SRC_TEST) -o test_nm

clean:
	@rm -f $(OBJ) $(OBJ_MAIN)

fclean:
	@rm -f $(OBJ) $(OBJ_MAIN)
	@rm -f $(NAME) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re debug
