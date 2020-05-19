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
#include "utils.h"
#include "error.h"
#include "client.h"
#include "server/database.h"

static uerror_t write_infos(const int fd, const char *name,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    uerror_t err = ERR_NONE;
    char *desc = remove_quotes(description);

    if (desc == NULL)
        return (ERR_MALLOC);
    if (write(fd, "name=", 5) < 0 ||
        write(fd, name, strlen(name)) < 0 ||
        write(fd, "\ndescription=", 13) < 0 ||
        write(fd, desc, strlen(desc)) < 0)
        err = _DISPLAY_PERROR("write - db_create_channel");
    free(desc);
    return (err);
}

static uerror_t create_info_file(const uuid_t team,
    char *channel, char *real_name,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_CHANNEL_PATH DB_INFO_FILE,
        uid_to_string(team), channel) < 0) {
        free(real_name);
        return (_DISPLAY_PERROR("asprintf - db_create_channel"));
    }
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0) {
        free(real_name);
        return (_DISPLAY_PERROR("open - db_create_channel"));
    }
    err = write_infos(fd, real_name, description);
    close(fd);
    free(path);
    free(real_name);
    return (err);
}

uerror_t db_create_channel(const uuid_t team,
    const char channel[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    uuid_t local;
    char *new_name = remove_quotes(channel);

    if (new_name == NULL)
        return (_DISPLAY_PERROR("remove_quotes - malloc", ERR_MALLOC));
    uuid_clear(local);
    uuid_generate_md5(local, local, new_name, strlen(new_name));
    if (asprintf(&path, DB_CHANNEL_PATH,
        uid_to_string(team), uid_to_string(local)) < 0) {
        free(new_name);
        return (_DISPLAY_PERROR("asprintf - db_create_channel"));
    }
    printf("Path for creating a new channel: '%s'\n", path);
    if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
        free(new_name);
        free(path);
        return (_DISPLAY_PERROR("mkdir - db_create_channel"));
    }
    free(path);
    return (create_info_file(team,
        uid_to_string(local), new_name, description));
}
