/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "error.h"
#include "client.h"
#include "server/database/database.h"

uerror_t db_send_pm(const client_t *src, const char *dest_id, const char *msg)
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;
    char *src_id = uid_to_string(src->id);

    if (asprintf(&path, DB_USER_PATH "%s", src_id, dest_id) < 0)
        return (_DISPLAY_PERROR("asprintf - db_send_pm"));
    if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) < 0)
        return (_DISPLAY_PERROR("open - db_send_pm"));
    free(path);
    path = NULL;
    if (asprintf(&path, "%s=%s\n", src_id, msg) < 0) {
        close(fd);
        return (_DISPLAY_PERROR("asprintf - db_send_pm"));
    }
    if (write(fd, path, strlen(path)) < 0)
        err = _DISPLAY_PERROR("write - db_send_pm");
    close(fd);
    free(path);
    return (err);
}

uerror_t db_get_all_message(const uuid_t author, const char *dest,
    char **buffer)
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;
    off_t offset;

    if (asprintf(&path, DB_USER_PATH "%s", uid_to_string(author), dest) < 0)
        return (_DISPLAY_PERROR("asprintf - db_get_all_message"));
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0)
        return (_DISPLAY_PERROR("open - db_get_all_message"));
    free(path);
    offset = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if ((*buffer = malloc(offset * sizeof(char))) == NULL) {
        close(fd);
        return (_DISPLAY_PERROR("db_get_all_message", ERR_MALLOC));
    }
    if (read(fd, *buffer, offset) < 0)
        err = _DISPLAY_PERROR("read - db_get_all_message");
    (*buffer)[offset - 1] = 0;
    close(fd);
    return (err);
}
