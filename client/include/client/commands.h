/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** commands.h
*/

#ifndef NWP_MYTEAMS_2019_COMMANDS_H
#define NWP_MYTEAMS_2019_COMMANDS_H

#include "socket.h"

#define NBR_FUNCTIONS   3

int help(socket_t *socket, char **args);
int login(socket_t *socket, char **args);
int logout(socket_t *socket, char **args);

char *commands[NBR_FUNCTIONS] = {
    "help",
    "login",
    "logout"
};

int (*command_functions[NBR_FUNCTIONS])(socket_t *, char **) = {
    help,
    login,
    logout
};

#endif
