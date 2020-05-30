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
#include "utils.h"

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

uerror_t db_user_add_sub(const client_t *client, const char *team)
{
    int fd;
    char *path = NULL;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_USER_PATH DB_SUB_FILE,
        uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_add_sub"));
    if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) < 0) {
        free(path);
        return (_DISPLAY_PERROR("open - db_user_add_sub"));
    }
    if (write(fd, team, strlen(team)) < 0 ||
        write(fd, "\n", 1) < 0)
        err = _DISPLAY_PERROR("write - db_user_add_sub");
    free(path);
    close(fd);
    return (err);
}

static uerror_t rewrite_file(const int fd, const char *path, const char *team)
{
    char **teams;
    uerror_t err;
    ushort new_size = 0;

    if ((err = get_file_content(fd, &teams)) != ERR_NONE)
        return (err);
    for (ushort i = 0; teams[i] != NULL; ++i) {
        if (strcmp(team, teams[i]) != 0) {
            new_size++;
            write(fd, teams[i], strlen(teams[i]));
        }
    }
    if (new_size == 0)
        remove(path);
    free_char_tab(teams);
    return (ERR_NONE);
}

uerror_t db_user_remove_sub(const client_t *client, const char *team)
{
    int fd;
    char *path = NULL;
    uerror_t err;

    if (asprintf(&path, DB_USER_PATH DB_SUB_FILE,
        uid_to_string(client->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_add_sub"));
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0) {
        free(path);
        return (_DISPLAY_PERROR("open - db_user_add_sub"));
    }
    err = rewrite_file(fd, path, team);
    close(fd);
    free(path);
    return (err);
}
