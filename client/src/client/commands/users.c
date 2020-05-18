/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** users.c
*/

#include "client/commands.h"
#include "client/utils.h"
#include "error.h"

int users(socket_t *socket, char **args)
{
    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    if (get_server_response(socket->sock_fd) == NULL)
        return (ERR_INIT);
    return (ERR_NONE);
}
