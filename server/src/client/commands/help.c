/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "server/database/database.h"
#include "client/commands.h"

uerror_t show_help(_UNUSED_ server_t *s, const int c, _UNUSED_ const char **av)
{
    uerror_t err;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if ((err = send_reply(c, START_LISTING, "List of all commands:"))
        != ERR_NONE)
        return (err);
    for (short i = 0; CLIENT_COMMANDS[i].name != NULL; ++i) {
        err = send_reply(c, LISTING, "Command: %s", CLIENT_COMMANDS[i].name);
        if (err != ERR_NONE)
            return (err);
    }
    return (send_reply(c, END_LISTING, NULL));
}
