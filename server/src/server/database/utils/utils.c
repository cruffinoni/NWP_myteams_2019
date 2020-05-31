/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server/database/database.h"
#include "utils.h"

static off_t get_file_size(const int fd)
{
    off_t size;

    if ((size = lseek(fd, 0, SEEK_END)) < 0 || lseek(fd, 0, SEEK_SET) < 0)
        return (_DISPLAY_PERROR("lseek - get_file_size", -1));
    return (size);
}

uerror_t get_file_content(const int fd, char ***output)
{
    off_t size = get_file_size(fd);
    char *buffer = malloc(sizeof(char) * size + 1);

    if (buffer == NULL)
        return (_DISPLAY_PERROR("malloc - get_file_content", ERR_MALLOC));
    if (read(fd, buffer, size) < 0) {
        free(buffer);
        return (_DISPLAY_PERROR("read - get_file_content"));
    }
    buffer[size] = '\0';
    if ((*output = str_to_array(buffer)) == NULL) {
        free(buffer);
        return (_DISPLAY_PERROR("str_to_array - get_file_content", ERR_MALLOC));
    }
    free(buffer);
    if (lseek(fd, 0, SEEK_SET) < 0) {
        free_char_tab(*output);
        return (_DISPLAY_PERROR("lseek - get_file_content"));
    }
    return (ERR_NONE);
}

char *db_get_uuid_str(const char *id)
{
    uuid_t local;

    uuid_clear(local);
    uuid_generate_md5(local, local, id, strlen(id));
    return (uid_to_string(local));
}

bool db_path_exists(const char *path, ...)
{
    char *path_fmt = NULL;
    int acc;
    va_list list;

    va_start(list, path);
    if (vasprintf(&path_fmt, path, list) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_exists", false));
    acc = access(path_fmt, R_OK | W_OK);
    free(path_fmt);
    va_end(list);
    return (acc == 0);
}
