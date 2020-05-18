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
    if ((err = read_user_info_file(id, dest)) != ERR_NONE)
        return (err);
    return (ERR_NONE);
}

static uerror_t add_node(db_user_list_t **list, client_t *buffer)
{
    db_user_list_t *node = malloc(sizeof(db_user_list_t));

    if (node == NULL)
        return (_DISPLAY_PERROR("malloc", ERR_MALLOC));
    uuid_clear(node->client.id);
    uuid_generate_md5(node->client.id, node->client.id, buffer->name,
        MAX_NAME_LENGTH);
    strcpy(node->client.name, buffer->name);
    node->next = *list;
    *list = node;
    return (ERR_NONE);
}

void db_destroy_user_list(db_user_list_t *header)
{
    db_user_list_t *curr = header;
    db_user_list_t *next;

    if (header == NULL)
        return;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

uerror_t db_get_all_users(db_user_list_t **dest)
{
    struct dirent *dirent;
    DIR *dir = opendir(DB_USER_FOLDER);
    uerror_t err;
    client_t local;

    if (dir == NULL)
        return (_DISPLAY_PERROR("opendir - db_get_all_users"));
    while ((dirent = readdir(dir)) != NULL) {
        if (index(dirent->d_name, '.') != NULL)
            continue;
        if ((err = read_user_info_file(dirent->d_name, &local)) != ERR_NONE ||
            (err = add_node(dest, &local)) != ERR_NONE) {
            closedir(dir);
            db_destroy_user_list(*dest);
            return (err);
        }
    }
    closedir(dir);
    return (ERR_NONE);
}
