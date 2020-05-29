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

static uerror_t create_info_file(const char *team_name,
    const char *original_name, const char *channel,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_CHANNEL_PATH DB_INFO_FILE,
        team_name, channel) < 0) {
        return (_DISPLAY_PERROR("asprintf - db_create_channel"));
    }
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0) {
        free(path);
        return (_DISPLAY_PERROR("open - db_create_channel"));
    }
    err = write_infos(fd, original_name, description);
    close(fd);
    free(path);
    return (err);
}

uerror_t db_create_channel(const uuid_t team,
    const char *channel,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    char *channel_name = db_get_uuid_str(channel);
    uuid_name_t team_name = {0};

    uuid_unparse_lower(team, team_name);
    printf("Team name: '%s'\n", team_name);
    if (asprintf(&path, DB_CHANNEL_PATH, team_name, channel_name) < 0) {
        return (_DISPLAY_PERROR("asprintf - db_create_channel"));
    }
    printf("Path for creating a new channel: '%s'\n", path);
    if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
        free(path);
        return (_DISPLAY_PERROR("mkdir - db_create_channel"));
    }
    free(path);
    return (create_info_file(team_name, channel, channel_name, description));
}

