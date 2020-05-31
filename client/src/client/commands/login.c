/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** login.c
*/

#include <uuid/uuid.h>
#include <stdlib.h>
#include "socket.h"
#include "error.h"
#include "uid.h"
#include "utils.h"
#include "client/utils.h"
#include "myteams/logging_client.h"

static char *get_user_uuid(char const *server_response)
{
    char *s_uuid = malloc(sizeof(char) * UUID_MAX_NAME);
    int i = 0;
    int k = 0;

    if (s_uuid == NULL)
        return (NULL);
    for (i = 0; server_response[i] != '<'; ++i);
    ++i;
    while (server_response[i] != '>') {
        s_uuid[k] = server_response[i];
        ++i;
        ++k;
    }
    s_uuid[k] = '\0';
    return (s_uuid);
}

int login_success(socket_t *socket, char *server_response)
{
    char *user_id = get_user_uuid(server_response);

    if (user_id == NULL)
        return (ERR_INIT);
    if (client_event_loggedin(user_id, socket->client->name) == -1) {
        free(user_id);
        return (ERR_INIT);
    }
    if (uuid_parse(user_id, socket->client->id) < 0) {
        free(user_id);
        return (ERR_INIT);
    }
    free(user_id);
    socket->client->flags = CLIENT_CONNECTED;
    return (ERR_NONE);
}

int login(socket_t *socket, char **args)
{
    if (send_server_message(socket->sock_fd, args) == ERR_INIT)
        return (ERR_INIT);
    if (tab_len(args) == 2)
        set_client_username(socket, args[1]);
    return (ERR_NONE);
}
