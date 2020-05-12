/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stddef.h>
#include <stdlib.h>

static int valid_char(const char c, const char k)
{
    return ((c >= 32 && c <= 126) && c != ' ' && c != k);
}

static int count_words(char const *str, const char c)
{
    int total_count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (valid_char(str[i], c) && !in_word) {
            in_word = 1;
            total_count++;
        }
        if (!valid_char(str[i], c))
            in_word = 0;
    }
    return (total_count);
}

static void malloc_tab(char **tab, char const *str, const char c)
{
    int previous_size = 0;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (valid_char(str[i], c))
            previous_size++;
        else if (previous_size > 0) {
            tab[j++] = malloc(sizeof(char) * (previous_size + 1));
            previous_size = 0;
        }
    }
    if (previous_size > 0)
        tab[j++] = malloc(sizeof(char) * (previous_size + 1));
    tab[j] = NULL;
}

static void fill_tab(char **tab, char const *str, const char c)
{
    int j = 0;
    int k = 0;
    int words = count_words(str, c);

    for (int i = 0; str[i] != '\0' && j < words; i++) {
        if (valid_char(str[i], c))
            tab[j][k++] = str[i];
        else if (k > 0) {
            tab[j++][k] = '\0';
            k = 0;
        }
    }
    if (words > 0 && k > 0)
        tab[j][k] = '\0';
}

char **str_to_array_ex(char const *str, const char c)
{
    char **tab = NULL;
    int words = count_words(str, c);

    tab = malloc(sizeof(char *) * (words + 1));
    if (tab == NULL)
        return (NULL);
    malloc_tab(tab, str, c);
    fill_tab(tab, str, c);
    return (tab);
}
