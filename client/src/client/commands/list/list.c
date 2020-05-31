/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** list.c
*/

#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "client/commands.h"
#include "client/utils.h"
#include "communication/codes.h"
#include "client/list.h"

static int fetch_by_category(char const *line, char *category,
    int len_category)
{
    char *list_categories[] = {"User", "Teams", NULL};
    int (*list_f[])(char const *, int) = {list_users, list_teams, NULL};

    for (int i = 0; list_categories[i]; ++i) {
        if (strcmp(category, list_categories[i]) == 0 &&
            list_f[i](line, len_category + 7) == ERR_INIT) {
            free(category);
            return (ERR_INIT);
        }
    }
    free(category);
    return (ERR_NONE);
}

static int handle_list_elem(char const *line)
{
    char *category = NULL;
    int len_category = 0;
    int k = 5;

    for (int i = k; line[i] != ' '; ++i, ++len_category);
    category = malloc(sizeof(char) * (len_category + 1));
    if (category == NULL)
        return (ERR_INIT);
    for (int i = 0; line[k] != ' '; ++k, ++i)
        category[i] = line[k];
    category[len_category] = '\0';
    return (fetch_by_category(line, category, len_category));
}

int get_list_data(socket_t _UNUSED_ *params, char *server_response)
{
    char *line = NULL;
    int len_line = 1;
    int i = 0;

    while (len_line > 0) {
        len_line = get_line(&line, server_response, &i);
        if (len_line == -1)
            return (ERR_INIT);
        if (line != NULL && get_status_code(line) == LISTING &&
        handle_list_elem(line) == ERR_INIT) {
            free(line);
            return (ERR_INIT);
        }
        free(line);
        line = NULL;
    }
    return (ERR_NONE);
}
