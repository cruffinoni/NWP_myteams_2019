/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** shell.c - file used to handle commands
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "socket.h"
#include "utils.h"
#include "error.h"
#include "client/shell.h"
#include "client/utils.h"
#include "communication/codes.h"

static void print_client_prompt(socket_t *params)
{
    printf("\033[1;31m[%s:%ld] ", params->ip, params->port);
    if (params->client != NULL)
        printf("\033[1;34m%s ", params->client->name);
    printf("\033[1;33m➜ \033[1;37m");
    fflush(stdout);
}

static int check_connection_to_server(socket_t *socket)
{
    char *server_response = get_server_response(socket->sock_fd);

    if (server_response == NULL)
        return (ERR_INIT);
    if (get_status_code(server_response) != SERVICE_READY) {
        free(server_response);
        return (ERR_INIT);
    }
    free(server_response);
    return (ERR_NONE);
}

int shell(socket_t *params)
{
    char **user_entry = NULL;

    if (check_connection_to_server(params) == ERR_INIT)
        return (ERR_INIT);
    while (ACTIVE_SERVER) {
        print_client_prompt(params);
        user_entry = get_user_entry();
        if (user_entry == NULL)
            return (errno == 0 ? ERR_NONE : ERR_INIT);
        if (tab_len(user_entry) > 0)
            if (process_command(params, user_entry))
                return (ERR_INIT);
        free_char_tab(user_entry);
    }
    return (ERR_NONE);
}
