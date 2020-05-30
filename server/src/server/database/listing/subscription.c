/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "server/server.h"
#include "server/database.h"

static uerror_t display_sub(const client_t *user, FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t rtn;
    uerror_t err;

    while ((rtn = getline(&line, &size, file)) > 0) {
        line[rtn - 1] = '\0';
        err = send_reply(user->socket, LISTING, "Team <%s>", line);
        free(line);
        if (err != ERR_NONE)
            return (err);
        line = NULL;
    }
    free(line);
    return (ERR_NONE);
}

uerror_t db_list_user_subscription(const client_t *user)
{
    FILE *file;
    char *path = NULL;
    uerror_t err;

    if (asprintf(&path, DB_USER_PATH DB_SUB_FILE, uid_to_string(user->id)) < 0)
        return (_DISPLAY_PERROR("asprintf - db_user_add_sub"));
    if (!db_path_exists(path)) {
        free(path);
        return (false);
    }
    if ((file = fopen(path, "r")) == NULL) {
        free(path);
        return (_DISPLAY_PERROR("open - db_user_add_sub"));
    }
    send_reply(user->socket, START_LISTING, NULL);
    err = display_sub(user, file);
    if (err == ERR_NONE)
        send_reply(user->socket, END_LISTING, NULL);
    fclose(file);
    free(path);
    return (err);
}

uerror_t db_list_team_subscriber(const int client, const uuid_name_t team_id)
{
    struct dirent *dirent;
    DIR *dir;
    uerror_t err;

    if ((dir = opendir(DB_USER_FOLDER)) == NULL)
        return (_DISPLAY_PERROR("opendir - db_list_team_subscriber"));
    if ((err = send_reply(client, START_LISTING, NULL)))
        return (err);
    while ((dirent = readdir(dir)) != NULL) {
        if (index(dirent->d_name, '.') != NULL)
            continue;
        if (db_user_is_subscribed_ss(dirent->d_name, (char *) team_id))
            err = send_reply(client, LISTING, "User <%s>", dirent->d_name);
        if (err != ERR_NONE) {
            closedir(dir);
            return (err);
        }
    }
    closedir(dir);
    if ((err = send_reply(client, END_LISTING, NULL)))
        return (err);
    return (ERR_NONE);
}
