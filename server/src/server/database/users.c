/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "server/database.h"

bool db_user_exists(const client_t *client)
{
    char *path = NULL;
    int acc;

    if (uuid_is_null(client->id))
        return (0);
    if (asprintf(&path, DB_USER_PATH "%s/", uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_exists", false));
    acc = access(path, R_OK | W_OK);
    free(path);
    return (acc == 0);
}

static uerror_t create_info_file(const client_t *client)
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_USER_INFO_FILE_PATH, uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_create_user"));
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0)
        return (_DISPLAY_PERROR("open - db_create_user"));
    if (write(fd, "name=", 5) < 0 ||
        write(fd, client->name, strlen(client->name)) < 0)
        err = _DISPLAY_PERROR("write - db_create_user");
    close(fd);
    free(path);
    return (err);
}

uerror_t db_create_user(const client_t *client)
{
    char *path = NULL;

    if (uuid_is_null(client->id)) {
        printf("db_create_user - client %p has a null uuid\n", client);
        return (ERR_NONE);
    }
    if (asprintf(&path, DB_USER_PATH "%s/", uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_create_user"));
    if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
        return (_DISPLAY_PERROR("mkdir - db_create_user"));
    printf("New user w/ path '%s' created\n", path);
    free(path);
    return (create_info_file(client));
}
