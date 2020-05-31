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

static char *set_uuid(const char *line, int *start)
{
    char *ret = NULL;
    int size = 0;

    for (int i = *start; line[i] != '>'; ++i, ++size);
    ret = malloc(sizeof(char) * (size + 1));
    if (ret == NULL)
        return (NULL);
    for (int i = 0; line[*start] != '>'; ++i, ++*start)
        ret[i] = line[*start];
    ret[size] = '\0';
    ++*start;
    return (ret);
}

static char *set_username(const char *line, int *start)
{
    char *ret = NULL;
    int size = 0;

    for (int i = *start; line[i] != ':'; ++i, ++size);
    ret = malloc(sizeof(char) * (size + 1));
    if (ret == NULL)
        return (NULL);
    for (int i = 0; line[*start] != ':'; ++i, ++*start)
        ret[i] = line[*start];
    ret[size] = '\0';
    ++*start;
    return (ret);
}

static int get_user_status(const char *line, int *start)
{
    char *nbr = malloc(sizeof(char) * 2);
    int to_ret;

    if (nbr == NULL)
        return (-1);
    nbr[0] = line[*start];
    nbr[1] = '\0';
    (*start) += 2;
    to_ret = (int) get_status_code(nbr);
    free(nbr);
    return (to_ret);
}

int list_users(char const *line, int start)
{
    int user_status = get_user_status(line, &start);
    char *username = set_username(line, &start);
    char *s_uuid = set_uuid(line, &start);

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
