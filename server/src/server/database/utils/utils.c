/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server/database.h"

char *db_get_uuid_str(const char *id)
{
    uuid_t local;

    uuid_clear(local);
    uuid_generate_md5(local, local, id, strlen(id));
    return (uid_to_string(local));
}

bool db_path_exists(const char *path, ...)
{
    char *path_fmt = NULL;
    int acc;
    va_list list;

    va_start(list, path);
    if (vasprintf(&path_fmt, path, list) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_exists", false));
    acc = access(path_fmt, R_OK | W_OK);
    free(path_fmt);
    va_end(list);
    return (acc == 0);
}
