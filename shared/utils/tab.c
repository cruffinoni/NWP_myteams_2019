/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>

void free_char_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}
