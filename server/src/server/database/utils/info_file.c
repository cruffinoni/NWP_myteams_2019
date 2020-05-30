/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "error.h"
#include "client.h"
#include "server/database.h"

static void extract_part(const char *buffer, char *dest, const ulong size)
{
    char *idx = index(buffer, '=');

    memset(dest, 0, size);
    strcpy(dest, "none");
    if (idx == NULL)
        return;
    strcpy(dest, idx + 1 * sizeof(char));
    if (dest[strlen(dest) - 1] == '\n')
        dest[strlen(dest) - 1] = '\0';
}

static uerror_t gather_data(FILE *file, char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH])
{
    char *buffer = NULL;
    size_t size = 0;
    ssize_t rtn;

    errno = 0;
    while ((rtn = getline(&buffer, &size, file)) > 0) {
        if (strstr(buffer, "name=") != NULL)
            extract_part(buffer, name, MAX_NAME_LENGTH);
        if (strstr(buffer, "description=") != NULL)
            extract_part(buffer, description, MAX_DESCRIPTION_LENGTH);
        free(buffer);
        buffer = NULL;
    }
    free(buffer);
    return (rtn != 0 && errno != 0 ? _DISPLAY_PERROR("getline") : ERR_NONE);
}

uerror_t read_info_file(const char *full_path, char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH])
{
    char *path = NULL;
    FILE *file;
    uerror_t err;

    if (asprintf(&path, "%s.info", full_path) < 0)
        return (_DISPLAY_PERROR("asprintf - read_info_file"));
    if ((file = fopen(path, "r")) == NULL) {
        free(path);
        return (_DISPLAY_PERROR("fopen - read_info_file"));
    }
    err = gather_data(file, name, description);
    free(path);
    fclose(file);
    return (err);
}

uerror_t read_info_thread_file(const char *full_path,
    char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH])
{
    FILE *file;
    uerror_t err;

    if ((file = fopen(full_path, "r")) == NULL)
        return (_DISPLAY_PERROR("fopen - read_info_thread_file"));
    err = gather_data(file, name, description);
    fclose(file);
    return (err);
}
