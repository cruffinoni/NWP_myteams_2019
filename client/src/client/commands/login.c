/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** login.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"
#include "utils.h"
#include "error.h"
#include "client/shell.h"

static int get_len_string_with_tab(char **tab)
{
    int len = 0;

    for (int i = 0; tab[i]; ++i) {
        for (int x = 0; tab[i][x]; ++x)
            ++len;
        ++len;
    }
    return (len);
}

static char *format_send_data(char **args)
{
    int len = get_len_string_with_tab(args);
    char *to_send = malloc(sizeof(char) * len);
    int increment = 0;

    if (to_send == NULL)
        return (NULL);
    for (int i = 0; args[i]; ++i) {
        for (int x = 0; args[i][x]; ++x, ++increment)
            to_send[increment] = args[i][x];
        to_send[increment] = ' ';
        ++increment;
    }
    to_send[len - 1] = '\0';
    return (to_send);
}

int login(socket_t *socket, char **args)
{
    char *to_send = format_send_data(args);
    int message_length;
    char *server_response;

    if (to_send == NULL) {
        printf("Error malloc\n");
        return (ERR_INIT);
    }
    message_length = get_strlen(to_send);
    if (write(socket->sock_fd, to_send, message_length) < 0) {
        free(to_send);
        printf("Error write\n");
        return (ERR_INIT);
    }
    free(to_send);
    server_response = get_server_response(socket->sock_fd);
    if (server_response == NULL)
        return (ERR_INIT);
    return (ERR_NONE);
}
