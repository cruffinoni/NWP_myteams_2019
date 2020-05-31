/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** main.c - mainfile for client teams
*/

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "error.h"
#include "socket.h"
#include "client/shell.h"
#include "client/utils.h"

void free_params(socket_t *params)
{
    if (params == NULL)
        return;
    free_user(params);
    if (params->ip != NULL)
        free(params->ip);
    if (params->sock_fd > 0)
        close(params->sock_fd);
    free(params);
}

static void catch_signal(int signal_id)
{
    if (signal_id == SIGINT)
        ACTIVE_SERVER = false;
    else if (signal_id == SIGPIPE)
        printf("SIGPIPE caught...\n");
}

static int init_client(char **av)
{
    socket_t *params = NULL;

    params = init_client_connection(av);
    if (params == NULL) {
        free_params(params);
        return (ERR_INIT);
    }
    if (signal(SIGINT, &catch_signal) == SIG_ERR ||
        signal(SIGPIPE, &catch_signal) == SIG_ERR) {
        printf("Signal error\n");
        free_params(params);
        return (ERR_INIT);
    }
    if (shell(params) == ERR_INIT) {
        free_params(params);
        return (ERR_INIT);
    }
    free_params(params);
    return (ERR_NONE);
}

int main(int ac, char **av)
{
    if (ac == 3) {
        if (setvbuf(stdout, NULL, _IONBF, 0) != 0) {
            printf("Error setvbuf\n");
            return (ERR_INIT);
        }
        return (init_client(av));
    }
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n");
        printf("\tip    is the server ip address on which ");
        printf("the server socket listens\n");
        printf("\tport  is the port number on which ");
        printf("the server socket listens\n");
        return (ERR_NONE);
    }
    printf("Wrong usage. Start with -help to see help.\n");
    return (ERR_INIT);
}
