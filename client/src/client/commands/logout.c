/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** logout.c
*/

#include <stdlib.h>
#include "error.h"
#include "socket.h"
#include "client/utils.h"
#include "communication/codes.h"
#include "myteams/logging_client.h"

static int log_lib(socket_t *socket)
{
    char *user_id = uid_to_string(socket->client->id);

    if (client_event_loggedout(user_id, socket->client->name) == -1)
        return (ERR_INIT);
    return (ERR_NONE);
}

int logout(socket_t *socket, char **args)
{
    char *server_response;

    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    server_response = get_server_response(socket->sock_fd);
    if (server_response == NULL)
        return (ERR_INIT);
    if (get_status_code(server_response) == DISCONNECTED) {
        if (log_lib(socket) == ERR_INIT) {
            free(server_response);
            return (ERR_INIT);
        }
        free_user(socket);
    }
    free(server_response);
    return (ERR_NONE);
}
