/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "server/database/database.h"
#include "client/commands.h"
#include "utils.h"

static uerror_t release_local_event(const uuid_t client, const char *team,
    const bool join, const uerror_t err)
{
    if (err != ERR_NONE)
        return (err);
    if (join) {
        if (server_event_user_join_a_team(team,
            uid_to_string(client)) < 0)
            return (_DISPLAY_PERROR("api"));
    }
    else if (server_event_user_leave_a_team(team,
        uid_to_string(client)) < 0)
            return (_DISPLAY_PERROR("api"));
    return (ERR_NONE);
}

uerror_t subscribe(server_t *s, const int c, const char **av)
{
    uuid_t local;
    uerror_t err;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, FORBIDDEN, NULL));
    if (uuid_parse(av[1], local) < 0)
        return (send_reply(s->client[c]->socket, INVALID_ID_PROVIDED, NULL));
    if (!db_team_exists(local))
        return (send_reply(s->client[c]->socket, ID_DOESNT_EXISTS,
            "Team <%s> doesn't exists.", av[1]));
    if (db_user_is_subscribed(s->client[c], local))
        return (send_reply(s->client[c]->socket, ID_ALREADY_EXISTS,
            "User already subscribed to this team"));
    err = db_user_add_sub(s->client[c], av[1]);
    if (err != ERR_NONE)
        send_reply(s->client[c]->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(s->client[c]->socket, OK, NULL);
    return (release_local_event(s->client[c]->id, av[1], true, err));
}

uerror_t unsubscribe(server_t *s, const int c, const char **av)
{
    uuid_t local;
    uerror_t err;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, FORBIDDEN, NULL));
    if (uuid_parse(av[1], local) < 0)
        return (send_reply(s->client[c]->socket, INVALID_ID_PROVIDED, NULL));
    if (!db_team_exists(local))
        return (send_reply(s->client[c]->socket, ID_DOESNT_EXISTS,
            "Team <%s> doesn't exists.", av[1]));
    if (!db_user_is_subscribed(s->client[c], local))
        return (send_reply(s->client[c]->socket, ID_ALREADY_EXISTS,
            "User is not subscribed to this team"));
    err = db_user_remove_sub(s->client[c], av[1]);
    if (err != ERR_NONE)
        send_reply(s->client[c]->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(s->client[c]->socket, OK, NULL);
    return (release_local_event(s->client[c]->id, av[1], false, err));
}

uerror_t subscription(server_t *s, const int c, const char **av)
{
    uuid_t local;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, FORBIDDEN, NULL));
    if (tab_len((char **) av) == 1)
        return (db_list_user_subscription(s->client[c]));
    else {
        if (uuid_parse(av[1], local) < 0)
            return (send_reply(s->client[c]->socket,
                INVALID_ID_PROVIDED, NULL));
        if (!db_team_exists(local))
            return (send_reply(s->client[c]->socket, ID_DOESNT_EXISTS,
                "Team <%s> doesn't exists.", av[1]));
        return (db_list_team_subscriber(c, av[1]));
    }
}
