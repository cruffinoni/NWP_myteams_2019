##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##

CLIENT			=	./client
CLIENT_BINARY	=	myteams_cli

SERVER			=	./server
SERVER_BINARY	=	myteams_server

all: $(CLIENT) $(SERVER)

$(CLIENT):
	$(MAKE) -C $(CLIENT)
	cp $(CLIENT)/$(CLIENT_BINARY) .

$(SERVER):
	$(MAKE) -C $(SERVER)
	cp $(SERVER)/$(SERVER_BINARY) .

debug:
	$(MAKE) -C $(SERVER) debug
	$(MAKE) -C $(CLIENT) debug

clean:
	$(MAKE) -C $(SERVER) clean
	$(MAKE) -C $(CLIENT) clean

fclean:
	$(MAKE) -C $(SERVER) fclean
	$(MAKE) -C $(CLIENT) fclean

re:	fclean all

.PHONY:	all clean fclean re debug client server
