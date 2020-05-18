/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** string.c - file used to manipulate strings
*/
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void str_to_lower_case(char *str)
{
    for (int i = 0; str[i]; ++i)
        str[i] = (char) tolower(str[i]);
}

char *remove_quotes(const char *original)
{
    const size_t len = strlen(original);
    char *fmt = NULL;
    size_t k = 0;

    if (original[0] != '\"' || original[len - 1] != '\"')
        return (strdup(original));
    if ((fmt = malloc(len)) == NULL)
        return (fmt);
    for (size_t i = 1; i < len - 1; ++i)
        fmt[k++] = original[i];
    fmt[k] = '\0';
    return (fmt);
}
