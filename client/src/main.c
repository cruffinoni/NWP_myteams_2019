/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** main.c - mainfile for client teams
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "error.h"
#include "socket.h"

static int init_client(char **av)
{
    socket_t *params = NULL;

    params = init_client_connection(av);
    if (params == NULL) {
        free_params(params);
        return (ERR_INIT);
    }
    return (ERR_NONE);
}

void free_params(socket_t *params)
{
    if (params->ip != NULL)
        free(params->ip);
    if (params->sock_fd < 0)
        close(params->sock_fd);
    free(params);
}

int main(int ac, char **av)
{
    if (ac == 3)
        return (init_client(av));
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n");
        printf("\tip    is the server ip address on which ");
        printf("the server socket listens\n");
        printf("\tport  is the port number on which ");
        printf("the server socket listens\n");
        return (ERR_NONE);
    }
    fprintf(stderr, "Wrong usage. Start with -help to see help.\n");
    return (ERR_INIT);
}
