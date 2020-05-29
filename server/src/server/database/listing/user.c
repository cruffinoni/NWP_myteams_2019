/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "error.h"
#include "client.h"
#include "server/database.h"

uerror_t db_get_user_infos(const char *id, client_t *dest)
{
    char *path = NULL;
    int acc;
    uerror_t err;

    if (asprintf(&path, DB_USER_PATH, id) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_exists", false));
    acc = access(path, R_OK | W_OK);
    memset(dest->name, 0, MAX_NAME_LENGTH);
    free(path);
    if (acc != 0)
        return (ERR_NONE);
    if ((err = read_info_file(id, dest->name, NULL)) != ERR_NONE)
        return (err);
    return (ERR_NONE);
}

static uerror_t use_folder_name(db_listing_t **dest, const char d_name[256])
{
    char *path = NULL;
    uerror_t err;
    char name[MAX_NAME_LENGTH] = {0};

    if (asprintf(&path, DB_USER_PATH, d_name) < 0)
        return (_DISPLAY_PERROR("asprintf - use_folder_name"));
    if ((err = read_info_file(path, name, NULL)) == ERR_NONE)
        err = add_node(dest, name, NULL);
    free(path);
    return (err);
}

uerror_t db_list_users(db_listing_t **dest)
{
    struct dirent *dirent;
    DIR *dir = opendir(DB_USER_FOLDER);
    uerror_t err;

    if (dir == NULL)
        return (_DISPLAY_PERROR("opendir - db_list_users"));
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
