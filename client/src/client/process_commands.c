/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** process_commands.c - file who take args and execute is proper function
*/

#include <stdio.h>
#include <string.h>
#include "client/commands.h"
#include "utils.h"
#include "error.h"

int process_command(socket_t *socket, char **args)
{
    char *commands[] = {"help", "login", "logout", "users", "user", "send",
        "messages", "subscribe", "subscribed", "unsubscribe", "use",
        "create", "list", "info", NULL};
    int (*command_functions[])(socket_t *, char **) = {help, login, logout,
        users, user, send, messages, subscribe, subscribed, unsubscribe,
        use, create, list, info, NULL};

    str_to_lower_case(args[0]);
    for (int i = 0; commands[i]; ++i) {
        if (strcmp(commands[i], args[0]) == 0) {
            if (command_functions[i](socket, args))
                return (ERR_INIT);
            return (ERR_NONE);
        }
    }
    printf("Commande non reconnue : %s\n", args[0]);
    return (ERR_NONE);
}
