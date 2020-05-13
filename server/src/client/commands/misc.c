/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "error.h"
#include "client.h"
#include "server/server.h"
#include "client/management.h"

uerror_t disconnect_client(server_t *server,
    const int client, _UNUSED_ const char **args)
{
    //if (!IS_CONNECTED(server->client[client]))
    //    return (send_reply(client, NOT_CONNECTED, NULL));
    FD_CLR(client, &server->active_fd);
    //server_event_user_logged_out(server->client[client]->id);
    free_client(&server->client[client]);
    return (ERR_NONE);
}
