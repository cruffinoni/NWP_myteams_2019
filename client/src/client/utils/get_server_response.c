/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** get_server_response.c - get server response from server
*/

#include <string.h>
#include <client.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "socket.h"

long get_status_code(char *server_response)
{
    return (strtol(server_response, NULL, 10));
}

char *get_server_response(socket_t *params)
{
    char *buffer = malloc(sizeof(char) * MAX_REQUEST_LENGTH);
    ssize_t rtn;

    if (buffer == NULL)
        return (NULL);
    if (select(MAX_CONNECTION, &params->server_set, NULL, NULL,
        NULL) < 0 && errno != EINTR) {
        printf("Error select\n");
        free(buffer);
        return (NULL);
    }
    memset(buffer, 0, MAX_REQUEST_LENGTH);
    rtn = read(params->sock_fd, buffer, MAX_REQUEST_LENGTH);
    if (rtn < 0) {
        printf("Error read\n");
        return (NULL);
    }
    printf("%s", buffer);
    return (buffer);
}
