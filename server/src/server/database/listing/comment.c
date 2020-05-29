/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "server/database.h"

static int strfind(const char *s, const char c)
{
    for (size_t i = 0, j = strlen(s); i < j ; ++i)
        if (c == s[i])
            return (i);
    return (-1);
}

static uerror_t extract_name(const char *buffer, char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH])
{
    int idx = strfind(buffer, ':');
    int sec_idx;

    memset(name, 0, MAX_NAME_LENGTH);
    memset(description, 0, MAX_DESCRIPTION_LENGTH);
    if (idx == -1)
        return (ERR_CORRUPTED_FILE);
    memcpy(name, buffer, idx);
    sec_idx = strfind(buffer, '=');
    if (sec_idx == -1)
        return (ERR_CORRUPTED_FILE);
    memcpy(description, buffer + sec_idx + 1,
        strlen(buffer) - sec_idx);
    if (description[strlen(description) - 1] == '\n')
        description[strlen(description) - 1] = '\0';
    return (ERR_NONE);
}

static uerror_t extract_comments(db_listing_t **dest, FILE *file)
{
    ushort i = 0;
    char *buffer = NULL;
    size_t size = 0;
    ssize_t rtn;
    char name[MAX_NAME_LENGTH];
    uerror_t err;
    char description[MAX_DESCRIPTION_LENGTH];

    while ((rtn = getline(&buffer, &size, file)) > 0) {
        if (++i <= 2)
            continue;
        if ((err = extract_name(buffer, name, description)) != ERR_NONE ||
            (err = add_node(dest, name, description)) != ERR_NONE) {
            free(buffer);
            return (err);
        }
        free(buffer);
        buffer = NULL;
    }
    free(buffer);
    return (rtn != 0 && errno != 0 ? _DISPLAY_PERROR("getline") : ERR_NONE);
}

uerror_t db_list_comment(db_listing_t **dest, const client_contexts_t ctx)
{
    FILE *file = NULL;
    uerror_t err;
    char *path = NULL;
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};
    uuid_name_t thread_name = {0};

    uuid_unparse_lower(ctx[TEAM], team_name);
    uuid_unparse_lower(ctx[CHANNEL], channel_name);
    uuid_unparse_lower(ctx[THREAD], thread_name);
    if (asprintf(&path, DB_THREAD_PATH, team_name, channel_name, thread_name)
        < 0)
        return (_DISPLAY_PERROR("asprintf - db_list_thread"));
    if ((file = fopen(path, "r")) == NULL) {
        free(path);
        return (_DISPLAY_PERROR("fopen - read_info_file"));
    }
    err = extract_comments(dest, file);
    fclose(file);
    free(path);
    return (err);
}
