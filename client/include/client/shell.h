/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** shell.h
*/

#ifndef NWP_MYTEAMS_2019_SHELL_H
#define NWP_MYTEAMS_2019_SHELL_H

#include "socket.h"

int shell(socket_t *params);
char **get_user_entry();
int process_command(socket_t *socket, char **args);
char *get_server_response(int sock_fd);

#endif