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
#include "socket.h"
#include "error.h"
#include "client/utils.h"
#include "client/commands.h"
#include "communication/codes.h"

static int lib_interfacing(socket_t *params, char *buffer)
{
    long status_code = get_status_code(buffer);
    long codes[] = {LOGIN_SUCCESSFUL, DISCONNECTED, START_LISTING, -1};
    int (*log_list[])(socket_t *, char *) = {login_success, logout_success,
        get_list_data, NULL};

    for (int i = 0; codes[i] != -1; ++i) {
        if (status_code == codes[i] &&
        log_list[i](params, buffer) == ERR_INIT)
            return (ERR_INIT);
    }
    printf("%s", buffer);
    return (ERR_NONE);
}

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
    memset(buffer, 0, MAX_REQUEST_LENGTH);
    rtn = read(params->sock_fd, buffer, MAX_REQUEST_LENGTH);
    if (rtn < 0) {
        free(buffer);
        printf("Error read\n");
        return (NULL);
    }
    if (lib_interfacing(params, buffer) == ERR_INIT)
        return (NULL);
    return (buffer);
}
