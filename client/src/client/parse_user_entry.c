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

static char *get_buffer(void)
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

char **get_user_entry(void)
{
    char **args = NULL;
    char *buff = get_buffer();

    if (buff == NULL)
        return (NULL);
    args = str_to_array(buff);
    free(buff);
    return (args);
}
