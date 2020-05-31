/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** private_message.c
*/

#include <stdlib.h>
#include "myteams/logging_client.h"
#include "client/commands.h"
#include "error.h"

static void free_elems(char *uuid, char *msg)
{
    free(uuid);
    free(msg);
}

int private_message(char const *line, int start)
{
    char *s_uuid = NULL;
    char *message = NULL;

    while (line[start] != ':')
        ++start;
    ++start;
    s_uuid = set_data(line, &start, '>', 4);
    if (s_uuid == NULL)
        return (ERR_INIT);
    message = set_data(line, &start, '>', 0);
    if (message == NULL) {
        free(s_uuid);
        return (ERR_INIT);
    }
    if (client_event_private_message_received(s_uuid, message) == -1) {
        free_elems(s_uuid, message);
        return (ERR_INIT);
    }
    free_elems(s_uuid, message);
    return (ERR_NONE);
}