/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** process_commands.c - file who take args and execute is proper function
*/

#include <string.h>
#include "client/utils.h"
#include "client/commands.h"
#include "utils.h"
#include "error.h"

static int send_cmd(socket_t *socket, char **args)
{
    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    return (ERR_NONE);
}

int process_command(socket_t *socket, char **args)
{
    char *commands[] = {"/login", NULL};
    int (*command_functions[])(socket_t *, char **) = {login, NULL};

    str_to_lower_case(args[0]);
    for (int i = 0; commands[i]; ++i) {
        if (strcmp(commands[i], args[0]) == 0) {
            if (command_functions[i](socket, args))
                return (ERR_INIT);
            return (ERR_NONE);
        }
    }
    if (send_cmd(socket, args) == ERR_INIT)
        return (ERR_INIT);
    return (ERR_NONE);
}
