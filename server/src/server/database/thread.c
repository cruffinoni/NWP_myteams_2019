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
#include "server/database.h"

bool db_thread_exists(const uuid_t team, const uuid_t channel,
    const uuid_t thread)
{
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};

    uuid_unparse_lower(team, team_name);
    uuid_unparse_lower(channel, channel_name);
    return (db_path_exists(DB_THREAD_PATH, team_name, channel_name,
        uid_to_string(thread)));
}

bool db_thread_exists_str(const uuid_t team, const uuid_t channel,
    const char *thread)
{
    uuid_t local;
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};

    uuid_unparse_lower(team, team_name);
    uuid_unparse_lower(channel, channel_name);
    uuid_clear(local);
    uuid_generate_md5(local, local, thread, strlen(thread));
    return (db_path_exists(DB_THREAD_PATH, team_name, channel_name,
        uid_to_string(local)));
}

static uerror_t create_thread_file(char *path,
    const char *channel,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    int fd;
    uerror_t err = ERR_NONE;

    if ((fd = open(path, O_CREAT | O_RDWR, 0666)) < 0) {
        free(path);
        return (_DISPLAY_PERROR("open - db_create_thread"));
    }
    if (write(fd, "name=", 5) < 0 ||
        write(fd, channel, strlen(channel)) < 0 ||
        write(fd, "\ndescription=", 13) < 0 ||
        write(fd, description, strlen(description)) < 0)
        err = _DISPLAY_PERROR("write - db_create_thread");
    free(path);
    return (err);
}

uerror_t db_create_thread(const client_t *client,
    const char *thread,
    const char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    uuid_t local;
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};

    uuid_unparse_lower(client->context[TEAM], team_name);
    uuid_unparse_lower(client->context[CHANNEL], channel_name);
    uuid_clear(local);
    uuid_generate_md5(local, local, thread, strlen(thread));
    if (asprintf(&path, DB_THREAD_PATH, team_name, channel_name,
        uid_to_string(local)) < 0) {
        return (_DISPLAY_PERROR("asprintf - db_create_thread"));
    }
    printf("Path for creating a new thread: '%s'\n", path);
    return (create_thread_file(path, thread, description));
}
