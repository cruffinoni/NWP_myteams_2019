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
    const short params;
    commands_func_t func;
};

uerror_t disconnect_client(server_t *server,
    const int client, const char **args);
uerror_t login_client(server_t *server, const int client, const char **args);
uerror_t show_user_info(server_t *server, const int client, const char **args);
uerror_t show_all_users(server_t *server, const int client, const char **args);
uerror_t send_private_message(server_t *s, const int c,
    const char **av);
uerror_t list_private_message(server_t *s, const int c, const char **av);
uerror_t set_context(server_t *s, const int c, const char **args);
uerror_t create_command(server_t *server, const int client, const char **args);
uerror_t list_cmd(server_t *server, const int client,
    _UNUSED_ const char **args);
uerror_t subscribe(server_t *s, const int c, const char **av);
uerror_t unsubscribe(server_t *s, const int c, const char **av);
uerror_t subscription(server_t *s, const int c, const char **av);
uerror_t get_infos(server_t *s, const int c, const char **av);
uerror_t show_help(_UNUSED_ server_t *s, const int c, _UNUSED_ const char **av);

static const struct commands_data_s CLIENT_COMMANDS[] = {
    {"/logout",      0,  &disconnect_client},
    {"/login",       1,  &login_client},
    {"/user",        1,  &show_user_info},
    {"/users",       0,  &show_all_users},
    {"/send",        2,  &send_private_message},
    {"/messages",    1,  &list_private_message},
    {"/use",         -3, &set_context},
    {"/create",      -2, &create_command},
    {"/list",        0,  &list_cmd},
    {"/subscribe",   1,  &subscribe},
    {"/unsubscribe", 1,  &unsubscribe},
    {"/subscribed",  -1, &subscription},
    {"/info",        0,  &get_infos},
    {"/help",        0,  &show_help},
    {NULL,           0, NULL},
};

// Release event for create command
uerror_t release_event(const client_t *client, const server_t *server,
    const client_context_type_t type, const char **arg);
uerror_t parse_command(server_t *server, const int client, char **input);

#endif
