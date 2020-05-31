/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** list_teams.c
*/

#include <stdlib.h>
#include "error.h"
#include "myteams/logging_client.h"

char *set_data(const char *line, int *start, char delim, int to_inc)
{
    char *ret = NULL;
    int size = 0;

    while (line[*start + size] != delim)
        ++size;
    ret = malloc(sizeof(char) * (size + 1));
    if (ret == NULL)
        return (NULL);
    for (int i = 0; line[*start] != delim; ++i, ++*start)
        ret[i] = line[*start];
    ret[size] = '\0';
    *start += to_inc;
    return (ret);
}

static void free_elems(char *team_name, char *team_id, char *team_desc)
{
    if (team_name != NULL)
        free(team_name);
    if (team_id != NULL)
        free(team_id);
    if (team_desc != NULL)
        free(team_desc);
}

int list_teams(char const *line, int start)
{
    char *team_name = set_data(line, &start, ':', 1);
    char *team_id = set_data(line, &start, '>', 2);
    char *team_description = set_data(line, &start, '>', 0);

    if (team_name == NULL || team_id == NULL || team_description == NULL) {
        free_elems(team_name, team_id, team_description);
        return (ERR_INIT);
    }
    if (client_print_teams(team_id, team_name, team_description) == -1) {
        free_elems(team_name, team_id, team_description);
        return (ERR_INIT);
    }
    free_elems(team_name, team_id, team_description);
    return (ERR_NONE);
}
