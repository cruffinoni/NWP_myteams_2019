/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** login.c
*/

#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "error.h"
#include "client/utils.h"
#include "communication/codes.h"

int login(socket_t *socket, char **args)
{
    char *server_response;

    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    server_response = get_server_response(socket->sock_fd);
    if (server_response == NULL)
        return (ERR_INIT);
    if (get_status_code(server_response) == LOGIN_SUCCESSFUL &&
    init_user(socket, server_response, args[1]) == ERR_INIT) {
        free(server_response);
        return (ERR_INIT);
    }
    free(server_response);
    return (ERR_NONE);
}
