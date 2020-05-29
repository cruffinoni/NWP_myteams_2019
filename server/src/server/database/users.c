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
#include <dirent.h>
#include "error.h"
#include "client.h"
#include "server/database.h"
#include "myteams/logging_server.h"

bool db_user_exists(const client_t *client)
{
    return (db_path_exists(DB_USER_PATH, uid_to_string(client->id)));
}

bool db_user_exists_str(const char *id)
{
    return (db_path_exists(DB_USER_PATH, id));
}

static uerror_t create_info_file(const client_t *client)
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_USER_PATH DB_INFO_FILE,
        uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_create_user"));
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0)
        return (_DISPLAY_PERROR("open - db_create_user"));
    if (write(fd, "name=", 5) < 0 ||
        write(fd, client->name, strlen(client->name)) < 0)
        err = _DISPLAY_PERROR("write - db_create_user");
    close(fd);
    free(path);
    server_event_user_created(uid_to_string(client->id), client->name);
    return (err);
}

uerror_t db_create_user(const client_t *client)
{
    char *path = NULL;

    if (uuid_is_null(client->id)) {
        printf("db_create_user - client %p has a null uuid\n", client);
        return (ERR_NONE);
    }
    if (asprintf(&path, DB_USER_PATH, uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_create_user"));
    if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
        free(path);
        return (_DISPLAY_PERROR("mkdir - db_create_user"));
    }
    free(path);
    return (create_info_file(client));
}
