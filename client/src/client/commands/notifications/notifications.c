/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** notifications.c
*/

#include <string.h>
#include <stdlib.h>
#include "error.h"
#include "socket.h"
#include "client/commands.h"
#include "client/notifications.h"

static int fetch_by_category(char const *line, char *category,
    int len_category)
{
    char *list_categories[] = {"New PM from", NULL};
    int (*list_f[])(char const *, int) = {private_message, NULL};

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

int notifications(socket_t _UNUSED_ *params, char *line)
{
    char *category = NULL;
    int len_category = 0;
    int k = 5;

    for (int i = k; line[i] != '<'; ++i, ++len_category);
    category = malloc(sizeof(char) * (len_category + 1));
    if (category == NULL)
        return (ERR_INIT);
    for (int i = 0; line[k] != '<'; ++k, ++i)
        category[i] = line[k];
    --len_category;
    category[len_category] = '\0';
    return (fetch_by_category(line, category, len_category));
}
