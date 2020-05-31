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

static uerror_t use_folder_name(db_listing_t **dest, const char d_name[256])
{
    char *path = NULL;
    uerror_t err;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    if (asprintf(&path, DB_TEAM_PATH, d_name) < 0)
        return (_DISPLAY_PERROR("asprintf - use_folder_name"));
    if ((err = read_info_file(path, name, description)) == ERR_NONE)
        err = add_node(dest, name, description);
    free(path);
    return (err);
}

uerror_t db_list_teams(db_listing_t **dest)
{
    struct dirent *dirent;
    DIR *dir = opendir(DB_TEAM_FOLDER);
    uerror_t err;

    if (dir == NULL)
        return (_DISPLAY_PERROR("opendir - db_list_all_teams"));
    while ((dirent = readdir(dir)) != NULL) {
        if (index(dirent->d_name, '.') != NULL)
            continue;
        if ((err = use_folder_name(dest, dirent->d_name)) != ERR_NONE) {
            closedir(dir);
            db_destroy_listing(*dest);
            return (err);
        }
    }
    closedir(dir);
    return (ERR_NONE);
}
