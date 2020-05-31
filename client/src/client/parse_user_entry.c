/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** parse_user_entry.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client/shell.h"

int get_line(char **dest, char const *server_response, int *i)
{
    int line_len = 0;

    while (server_response[line_len + *i] &&
    server_response[line_len + *i] != '\n')
        ++line_len;
    if (line_len == 0)
        return (0);
    *dest = malloc(sizeof(char) * (line_len + 1));
    if (*dest == NULL)
        return (-1);
    for (int k = 0; k < line_len; ++k, ++*i) {
        if (server_response[*i] == '\0') {
            (*dest)[k] = '\0';
            return (-2);
        }
        (*dest)[k] = server_response[*i];
    }
    (*dest)[line_len] = '\0';
    ++*i;
    return (line_len);
}

void print_client_prompt(socket_t *params)
{
    printf("\033[1;31m[%s:%ld] ", params->ip, params->port);
    if (params->client->flags == CLIENT_CONNECTED)
        printf("\033[1;34m%s ", params->client->name);
    printf("\033[1;33m➜ \033[1;37m");
}

char *get_buffer(void)
{
    char *buffer = NULL;
    size_t line_buf_size = 0;
    ssize_t rtn;

    rtn = getline(&buffer, &line_buf_size, stdin);
    if (rtn == -1) {
        free(buffer);
        return (NULL);
    }
    return (buffer);
}
