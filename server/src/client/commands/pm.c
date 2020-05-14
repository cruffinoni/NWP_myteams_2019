/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "server/server.h"
#include "server/database.h"

static uerror_t check_local_uid(server_t *s, const int c, const char **av)
{
    uuid_t local;

    if (uuid_parse(av[1], local) < 0) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("uuid_parse - commands/pm.c", true));
    }
    if (!uuid_compare(local, s->client[c]->id))
        return (send_reply(c, INVALID_SYNTAX, NULL));
    if (!db_user_exists_id(av[1])) {
        send_reply(c, USER_DONT_EXIST, "User <%s> doesn't exists", av[1]);
        return (true);
    }
    return (false);
}

uerror_t send_private_message(server_t *s, const int c, const char **av)
{
    uerror_t err;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if ((err = check_local_uid(s, c, av)) != ERR_NONE)
        return (err != 0);
    if ((err = db_send_pm(s->client[c], av[1], av[2])) != ERR_NONE) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (err);
    }
    return (send_reply(c, OK, NULL));
}

uerror_t list_private_message(server_t *s, const int c, const char **av)
{
    uerror_t err;
    char *str = NULL;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if ((err = check_local_uid(s, c, av)) != ERR_NONE)
        return (err != 0);
    if ((err = db_get_all_message(s->client[c]->id, av[1], &str)) != ERR_NONE) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("db_get_all_message - cmds/pm.c", err));
    }
    err = send_reply(c, OK, "List: \"%s\"", str);
    free(str);
    return (err);
}
