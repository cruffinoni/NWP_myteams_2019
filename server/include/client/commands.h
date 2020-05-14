/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_COMMANDS
#define SRC_MYTEAMS_SERVER_COMMANDS

#include "server/server.h"

typedef uerror_t (*commands_func_t)(server_t *, const int, const char **);

struct commands_data_s {
    const char *name;
    const size_t params;
    commands_func_t func;
};

uerror_t disconnect_client(server_t *server,
    const int client, const char ** args);
uerror_t login_client(server_t *server, const int client, const char **args);
uerror_t show_user_info(server_t *server, const int client, const char **args);
uerror_t show_all_users(server_t *server, const int client, const char **args);

static const struct commands_data_s CLIENT_COMMANDS[] = {
    {"logout", 0, &disconnect_client},
    {"login", 1, &login_client},
    {"user", 1, &show_user_info},
    {"users", 0, &show_all_users},
    {NULL, 0, NULL},
};

uerror_t parse_command(server_t *server, const int client, char **input);

#endif
