/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "error.h"
#include "server/database.h"

static uerror_t use_folder_name(db_listing_t **dest, const char *src,
    const char d_name[256])
{
    char *path = NULL;
    uerror_t err;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    if (asprintf(&path, "%s%s", src, d_name) < 0)
        return (_DISPLAY_PERROR("asprintf - (channel) use_folder_name"));
    if ((err = read_info_thread_file(path, name, description)) == ERR_NONE)
        err = add_node(dest, name, description);
    free(path);
    return (err);
}

static uerror_t read_directory(const char *path, DIR *dir, db_listing_t **dest)
{
    struct dirent *dirent;
    uerror_t err;

    while ((dirent = readdir(dir)) != NULL) {
        if (strstr(dirent->d_name, ".thread") == NULL)
            continue;
        if ((err = use_folder_name(dest, path, dirent->d_name)) != ERR_NONE)
            return (err);
    }
    return (ERR_NONE);
}

uerror_t db_list_thread(db_listing_t **dest, const client_contexts_t ctx)
{
    DIR *dir = NULL;
    uerror_t err;
    char *path = NULL;
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};

    uuid_unparse_lower(ctx[TEAM], team_name);
    uuid_unparse_lower(ctx[CHANNEL], channel_name);
    if (asprintf(&path, DB_CHANNEL_PATH, team_name, channel_name) < 0)
        return (_DISPLAY_PERROR("asprintf - db_list_thread"));
    dir = opendir(path);
    if (dir == NULL) {
        free(path);
        return (_DISPLAY_PERROR("opendir - db_list_thread"));
    }
    err = read_directory(path, dir, dest);
    if (err != ERR_NONE)
        db_destroy_listing(*dest);
    free(path);
    closedir(dir);
    return (err);
}
