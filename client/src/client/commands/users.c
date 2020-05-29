/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** users.c
*/

#include <stdlib.h>
#include "client/commands.h"
#include "client/utils.h"
#include "error.h"

int users(socket_t *socket, char **args)
{
    char *server_response = NULL;

    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    server_response = get_server_response(socket);
    if (server_response == NULL)
        return (ERR_INIT);
    free(server_response);
    return (ERR_NONE);
}
