/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "error.h"
#include "server/database/database.h"
#include <stdio.h>

static uerror_t use_folder_name(db_listing_t **dest, const char *src,
    const char d_name[256])
{
    char *path = NULL;
    uerror_t err;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    if (asprintf(&path, "%s%s/", src, d_name) < 0)
        return (_DISPLAY_PERROR("asprintf - (channel) use_folder_name"));
    if ((err = read_info_file(path, name, description)) == ERR_NONE)
        err = add_node(dest, name, description);
    free(path);
    return (err);
}

static uerror_t read_directory(const char *path, DIR *dir, db_listing_t **dest)
{
    struct dirent *dirent;
    uerror_t err;

    while ((dirent = readdir(dir)) != NULL) {
        if (index(dirent->d_name, '.') != NULL)
            continue;
        if ((err = use_folder_name(dest, path, dirent->d_name)) != ERR_NONE)
            return (err);
    }
    return (ERR_NONE);
}

uerror_t db_list_channel(db_listing_t **dest, const char *team)
{
    DIR *dir = NULL;
    uerror_t err;
    char *path = NULL;

    if (asprintf(&path, DB_CHANNEL_FOLDER, team) < 0)
        return (_DISPLAY_PERROR("asprintf - db_list_channel"));
    dir = opendir(path);
    if (dir == NULL) {
        free(path);
        return (_DISPLAY_PERROR("opendir - db_list_all_teams"));
    }
    err = read_directory(path, dir, dest);
    if (err != ERR_NONE)
        db_destroy_listing(*dest);
    free(path);
    closedir(dir);
    return (err);
}
