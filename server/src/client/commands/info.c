/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include "server/database/database.h"
#include "client/commands.h"

static uerror_t get_user_infos(const client_t *this)
{
    return (send_reply(this->socket, OK, "Client's data <%s:%s>",
        this->name, uid_to_string(this->id)));
}

static uerror_t get_team_infos(const client_t *this)
{
    uuid_name_t team_str;
    char *path = NULL;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    uuid_unparse_lower(this->context[TEAM], team_str);
    if (asprintf(&path, DB_TEAM_PATH, team_str) < 0) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_team_infos"));
    }
    if (read_info_file(path, name, description) != ERR_NONE) {
        free(path);
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_team_infos"));
    }
    free(path);
    return (send_reply(this->socket, OK, "Selected team <%s:%s><%s>", team_str,
        name, description));
}

static uerror_t get_channel_infos(const client_t *this)
{
    uuid_name_t team_str;
    uuid_name_t channel_str;
    char *path = NULL;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    uuid_unparse_lower(this->context[TEAM], team_str);
    uuid_unparse_lower(this->context[CHANNEL], channel_str);
    if (asprintf(&path, DB_CHANNEL_PATH, team_str, channel_str) < 0) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_channel_infos"));
    }
    if (read_info_file(path, name, description) != ERR_NONE) {
        free(path);
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_channel_infos"));
    }
    free(path);
    return (send_reply(this->socket, OK, "Selected channel <%s:%s><%s>",
        channel_str, name, description));
}

static void convert_uuid_names(const client_contexts_t ctx, uuid_name_t team,
    uuid_name_t channel, uuid_name_t thread)
{
    uuid_unparse_lower(ctx[TEAM], team);
    uuid_unparse_lower(ctx[CHANNEL], channel);
    uuid_unparse_lower(ctx[THREAD], thread);
}

static uerror_t get_thead_infos(const client_t *this)
{
    uuid_name_t team_str;
    uuid_name_t channel_str;
    uuid_name_t thread;
    char *path = NULL;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    convert_uuid_names(this->context, team_str, channel_str, thread);
    if (asprintf(&path, DB_THREAD_PATH, team_str, channel_str, thread) < 0) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_channel_infos"));
    }
    if (read_info_thread_file(path, name, description) != ERR_NONE) {
        free(path);
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("asprintf - get_channel_infos"));
    }
    free(path);
    return (send_reply(this->socket, OK, "Selected thread <%s:%s><%s>",
        thread, name, description));
}

// /use a87876c5-4ff5-30a1-8924-028d4c40fd66 8613afd5-e446-383c-9677-2ce5e32806d0 7d934f2b-c6ac-37ec-95c6-f9eb8fc79239

uerror_t get_infos(server_t *s, const int c, _UNUSED_ const char **av)
{
    static uerror_t (*ptr_func[])(const client_t *) = {
        &get_user_infos, &get_team_infos, &get_channel_infos,
    };

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, FORBIDDEN, NULL));
    if (uuid_is_null(s->client[c]->context[TEAM]))
        return (send_reply(c, OK, "Client's data <%s:%s>", s->client[c]->name,
            uid_to_string(s->client[c]->id)));
    for (int i = 0; i < INVALID; ++i)
        if (uuid_is_null(s->client[c]->context[i]))
            return (ptr_func[i](s->client[c]));
    return (get_thead_infos(s->client[c]));
}
