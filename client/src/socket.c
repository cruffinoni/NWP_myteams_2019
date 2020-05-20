/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** socket.c - file used for socket creation
*/

#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "socket.h"

static bool check_port(char const *port)
{
    for (int i = 0; port[i]; ++i) {
        if (port[i] > '9' || port[i] < '0')
            return (false);
    }
    return (true);
}

static int create_socket(socket_t *params)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sockaddr;

    if (sock_fd < 0) {
        printf("Socket creation error\n");
        return (-1);
    }
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(params->port);
    inet_aton(params->ip, (struct in_addr *) &sockaddr.sin_addr.s_addr);
    if (connect(sock_fd, (const struct sockaddr *) &sockaddr,
        sizeof(struct sockaddr_un)) < 0) {
        printf("Connect error\n");
        return (-1);
    }
    return (sock_fd);
}

static int socket_creation(char **av, socket_t *params)
{
    if (!check_port(av[2])) {
        printf( "Erreur de syntaxe, le port doit ");
        printf( "être un nombre ou chiffre.\n");
        return (ERR_INIT);
    }
    params->ip = strdup(av[1]);
    if (params->ip == NULL) {
        free_params(params);
        return (ERR_INIT);
    }
    params->port = strtol(av[2], NULL, 10);
    params->sock_fd = create_socket(params);
    if (params->sock_fd < 0) {
        return (ERR_INIT);
    }
    printf("Trying to connect server: %s:%ld\n", params->ip,
        params->port);
    return (ERR_NONE);
}

socket_t *init_client_connection(char **av)
{
    socket_t *params = malloc(sizeof(socket_t));

    if (params == NULL)
        return (NULL);
    params->sock_fd = -1;
    params->port = -1;
    params->ip = NULL;
    params->client = NULL;
    if (socket_creation(av, params) == ERR_INIT) {
        free_params(params);
        return (NULL);
    }
    ACTIVE_SERVER = true;
    return (params);
}
