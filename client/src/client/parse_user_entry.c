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
#include "utils.h"

static char *get_buffer()
{
    char *buffer = malloc(sizeof(char) * MAX_REQUEST_LENGTH);
    ssize_t rtn;

    if (buffer == NULL)
        return (NULL);
    memset(buffer, 0, MAX_REQUEST_LENGTH);
    rtn = read(STDIN_FILENO, buffer, MAX_REQUEST_LENGTH);
    if (rtn <= 0) {
        if (rtn == -1)
            printf("Error read\n");
        free(buffer);
        return (NULL);
    }
    return (buffer);
}

char **get_user_entry()
{
    char **args = NULL;
    char *buff = get_buffer();

    if (buff == NULL)
        return (NULL);
    args = str_to_array(buff);
    free(buff);
    return (args);
}
