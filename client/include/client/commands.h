/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** commands.h
*/

#ifndef NWP_MYTEAMS_2019_COMMANDS_H
#define NWP_MYTEAMS_2019_COMMANDS_H

#include "socket.h"

#define _UNUSED_ __attribute__((unused))

//commands to send message to server
int login(socket_t *socket, char **args);

//functions to handle lib print
int get_list_data(socket_t *params, char *server_response);
int login_success(socket_t *socket, char *server_response);
int logout_success(socket_t *socket, char *server_resonse);
int forbidden(socket_t _UNUSED_ *params, char _UNUSED_ *server_response);

#endif
