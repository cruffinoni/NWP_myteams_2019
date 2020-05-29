/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <dirent.h>
#include <stdlib.h>
#include "server/database.h"
#include "client/commands.h"

//static uerror_t display_infofile_content()

static uerror_t list_teams(const int client)
{
    struct dirent *dirent;
    DIR *dir = opendir(DB_USER_FOLDER);

    if (dir == NULL) {
        _DISPLAY_PERROR("opendir - db_list_users");
        return (send_reply(client, INTERNAL_ERROR, NULL));
    }
}

uerror_t list_command(server_t *s, const int c, _UNUSED_ const char **av)
{
    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if (uuid_is_null(s->client[c]->context[TEAM]))
        return (list_teams(c));
}
