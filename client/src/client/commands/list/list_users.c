/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** list_users.c
*/

#include <stdlib.h>
#include "error.h"
#include "client/utils.h"
#include "myteams/logging_client.h"
#include "client/commands.h"

static int get_user_status(const char *line, int *start)
{
    char *nbr = malloc(sizeof(char) * 2);
    int to_ret;

    if (nbr == NULL)
        return (-1);
    nbr[0] = line[*start];
    nbr[1] = '\0';
    *start += 2;
    to_ret = (int) get_status_code(nbr);
    free(nbr);
    return (to_ret);
}

int list_users(char const *line, int start)
{
    int user_status = get_user_status(line, &start);
    char *username = set_data(line, &start, ':', 1);
    char *s_uuid = set_data(line, &start, '>', 0);

    if (username == NULL || s_uuid == NULL || user_status == -1) {
        if (username != NULL)
            free(username);
        if (s_uuid != NULL)
            free(s_uuid);
        return (ERR_INIT);
    }
    if (client_print_users(s_uuid, username, user_status) == -1) {
        free(username);
        free(s_uuid);
        return (ERR_INIT);
    }
    free(username);
    free(s_uuid);
    return (ERR_NONE);
}
