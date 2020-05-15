/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** shell.c - file used to handle commands
*/

#include <stdio.h>
#include "socket.h"
#include "client/shell.h"
#include "utils.h"

static void print_client_prompt(socket_t *params)
{
    printf("\033[1;31m[%s:%d] ", params->ip, params->port);
    if (params->client != NULL)
        printf("\033[1;34m%s ", params->client->name);
    printf("\033[1;33m➜ \033[1;37m");
    fflush(stdout);
}

void shell(socket_t *params)
{
    char **user_entry = NULL;

    while (ACTIVE_SERVER) {
        print_client_prompt(params);
        user_entry = get_user_entry();
        if (user_entry == NULL)
            return;
        free_char_tab(user_entry);
    }
}
