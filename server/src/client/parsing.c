/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "client/commands.h"
#include "utils.h"

uerror_t parse_command(server_t *server, const int client, char **input)
{
    if (input[0] == NULL)
        return (ERR_NONE);
    for (short i = 0; CLIENT_COMMANDS[i].name != NULL; ++i) {
        if (strcmp(CLIENT_COMMANDS[i].name, input[0]) != 0)
            continue;
        if (CLIENT_COMMANDS[i].params != tab_len(input) - 1)
            return (send_reply(client, INVALID_ARG_COUNT,
                "Invalid argument count, excepted %i got %i",
                CLIENT_COMMANDS[i].params, tab_len(input) - 1));
        _PRINT_CLIENT("[%i] Valid command: '%s'\n", client, input[0]);
        return (CLIENT_COMMANDS[i].func(server, client, (const char **) input));
    }
    _PRINT_CLIENT("[%i] Command '%s' not found\n", client, input[0]);
    return (send_reply(client, COMMAND_NOT_FOUND, NULL));
}
