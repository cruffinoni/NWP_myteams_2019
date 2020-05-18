/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** messages.c
*/

#include <stdlib.h>
#include "error.h"
#include "client/commands.h"
#include "client/utils.h"

int messages(socket_t *socket, char **args)
{
    char *server_response;

    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    server_response = get_server_response(socket->sock_fd);
    if (server_response == NULL)
        return (ERR_INIT);
    free(server_response);
    return (ERR_NONE);
}
