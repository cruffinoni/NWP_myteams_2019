/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** send_server_message.c - take an char ** to set in char *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "error.h"

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

int send_server_message(int sock_fd, char **args)
{
    char *to_send = format_send_data(args);
    size_t message_length;

    if (to_send == NULL) {
        printf("Error malloc\n");
        return (ERR_INIT);
    }
    message_length = strlen(to_send);
    if (write(sock_fd, to_send, message_length) < 0) {
        free(to_send);
        printf("Error write\n");
        return (ERR_INIT);
    }
    free(to_send);
    return (ERR_NONE);
}
