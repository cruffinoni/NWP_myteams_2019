/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "server/database.h"
#include "utils.h"

static bool check_teams(const int fd, const uuid_name_t team_name)
{
    uerror_t err;
    char **teams;

    if ((err = get_file_content(fd, &teams)) != ERR_NONE)
        return (err);
    for (ushort i = 0; teams[i] != NULL; ++i)
        if (!strcmp(team_name, teams[i])) {
            free_char_tab(teams);
            return (true);
        }
    free_char_tab(teams);
    return (false);
}

bool db_user_is_subscribed(const client_t *client, const uuid_t team)
{
    int fd;
    char *path = NULL;
    uuid_name_t team_name;

    uuid_unparse_lower(team, team_name);
    if (asprintf(&path, DB_USER_PATH DB_SUB_FILE, uid_to_string(client->id))
        < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_add_sub"));
    if (!db_path_exists(path)) {
        free(path);
        return (false);
    }
    if ((fd = open(path, O_RDWR)) < 0) {
        free(path);
        return (_DISPLAY_PERROR("open - db_user_add_sub"));
    }
    free(path);
    return (check_teams(fd, team_name));
}
