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

static uerror_t write_infos(const int fd, const char *team,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    uerror_t err = ERR_NONE;
    char *desc = remove_quotes(description);

    if (desc == NULL)
        return (ERR_MALLOC);
    if (write(fd, "name=", 5) < 0 ||
        write(fd, team, strlen(team)) < 0 ||
        write(fd, "\ndescription=", 13) < 0 ||
        write(fd, desc, strlen(desc)) < 0)
        err = _DISPLAY_PERROR("write - db_create_team");
    free(desc);
    return (err);
}

static uerror_t create_channel_directory(const char *path)
{
    char *channel_path = NULL;

    if (asprintf(&channel_path, "%schannel/", path) < 0)
        return (_DISPLAY_PERROR("asprintf - db_create_team"));
    if (mkdir(channel_path, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
        free(channel_path);
        return (_DISPLAY_PERROR("mkdir - create_channel_directory"));
    }
    free(channel_path);
    return (ERR_NONE);
}

static uerror_t create_info_file(char *team, char *real_name,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    int fd;
    uerror_t err = ERR_NONE;

    if (asprintf(&path, DB_TEAM_PATH DB_INFO_FILE, team) < 0) {
        free(real_name);
        return (_DISPLAY_PERROR("asprintf - db_create_team"));
    }
    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0) {
        free(real_name);
        return (_DISPLAY_PERROR("open - db_create_team"));
    }
    err = write_infos(fd, real_name, description);
    close(fd);
    free(path);
    free(real_name);
    return (err);
}

static uerror_t create_directories(const char *path)
{
    if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
        return (_DISPLAY_PERROR("mkdir - db_create_team"));
    return (create_channel_directory(path));
}

uerror_t db_create_team(const char team[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    uuid_t local;
    char *new_name = remove_quotes(team);

    if (new_name == NULL)
        return (_DISPLAY_PERROR("remove_quotes - malloc", ERR_MALLOC));
    uuid_clear(local);
    uuid_generate_md5(local, local, new_name, strlen(new_name));
    if (asprintf(&path, DB_TEAM_PATH, uid_to_string(local)) < 0 ||
        create_directories(path) != ERR_NONE) {
        free(new_name);
        free(path);
        return (_DISPLAY_PERROR("asprintf - db_create_team"));
    }
    free(path);
    return (create_info_file(uid_to_string(local), new_name, description));
}
