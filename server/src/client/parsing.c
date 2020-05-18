/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include <stdlib.h>
#include "client/commands.h"
#include "utils.h"

static bool has_enough_args(const short idx, const int client, char **input,
    uerror_t *err)
{
    const size_t tab_size = tab_len(input) - 1;
    const size_t params_abs = abs(CLIENT_COMMANDS[idx].params);

    if (CLIENT_COMMANDS[idx].params >= 0 && params_abs != tab_size) {
        *err = send_reply(client, INVALID_ARG_COUNT,
            "Invalid argument count, excepted %i but got %i",
            CLIENT_COMMANDS[idx].params, tab_size);
        return (false);
    } else if (CLIENT_COMMANDS[idx].params < 0 && tab_size > params_abs) {
        *err = send_reply(client, INVALID_ARG_COUNT,
            "Invalid argument count, excepted %i optional arg but got %i",
            params_abs, tab_size);
        return (false);
    }
    return (true);
}

uerror_t parse_command(server_t *server, const int client, char **input)
{
    uerror_t err = ERR_NONE;

    if (input[0] == NULL)
        return (ERR_NONE);
    for (short i = 0; CLIENT_COMMANDS[i].name != NULL; ++i) {
        if (strcmp(CLIENT_COMMANDS[i].name, input[0]) != 0)
            continue;
        if (!has_enough_args(i, client, input, &err))
            return (err);
        _PRINT_CLIENT("[%i] Valid command: '%s'\n", client, input[0]);
        return (CLIENT_COMMANDS[i].func(server, client, (const char **) input));
    }
    _PRINT_CLIENT("[%i] Command '%s' not found\n", client, input[0]);
    return (send_reply(client, COMMAND_NOT_FOUND, NULL));
}
