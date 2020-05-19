/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "error.h"
#include "client.h"
#include "server/server.h"
#include "server/database.h"

static uerror_t write_comment(const char *path, const char *comment)
{
    int fd;
    uerror_t err = ERR_NONE;

    if ((fd = open(path, O_WRONLY | O_APPEND)) < 0)
        return (_DISPLAY_PERROR("open - db_create_comment"));
    if (write(fd, comment, strlen(comment)) < 0)
        err = _DISPLAY_PERROR("write - db_create_comment");
    close(fd);
    return (err);
}

uerror_t db_create_comment(uuid_t client, client_contexts_t ctx,
    const char body[MAX_BODY_LENGTH])
{
    char *path = NULL;
    char *comment = NULL;
    uerror_t err;

    if (asprintf(&path, DB_THREAD_PATH, uid_to_string(ctx[TEAM]),
        uid_to_string(ctx[CHANNEL]), uid_to_string(ctx[THREAD])) < 0) {
        return (_DISPLAY_PERROR("asprintf - db_create_comment"));
    }
    if (asprintf(&comment, "\n<%s>:<%s>", uid_to_string(client), body) < 0) {
        free(path);
        return (_DISPLAY_PERROR("asprintf - db_create_comment"));
    }
    err = write_comment(path, comment);
    free(path);
    free(comment);
    return (err);
}
