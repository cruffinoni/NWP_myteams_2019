/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "error.h"
#include "client.h"
#include "server/database.h"

static void extract_user_name(const char *buffer, client_t *dest)
{
    char *idx = index(buffer, '=');

    memset(dest->name, 0, MAX_NAME_LENGTH);
    strcpy(dest->name, "none");
    if (idx == NULL)
        return;
    strcpy(dest->name, idx + 1 * sizeof(char));
}

uerror_t read_user_info_file(const char *folder_name, client_t *dest)
{
    char *path = NULL;
    FILE *file = 0;
    char *buffer = NULL;
    size_t size = 0;
    ssize_t rtn;

    if (asprintf(&path, DB_USER_PATH ".info", folder_name) < 0)
        return (_DISPLAY_PERROR("asprintf - read_user_info_file"));
    if ((file = fopen(path, "r")) == NULL) {
        free(path);
        return (_DISPLAY_PERROR("fopen - read_user_info_file"));
    }
    while ((rtn = getline(&buffer, &size, file)) > 0) {
        if (strstr(buffer, "name=") != NULL)
            extract_user_name(buffer, dest);
        free(buffer);
        buffer = NULL;
    }
    free(buffer);
    free(path);
    fclose(file);
    return (0);
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
