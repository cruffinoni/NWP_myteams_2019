/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** string.c - file used to manipulate strings
*/

void str_to_lower_case(char *str)
{
    for (int i = 0; str[i]; ++i) {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] += 32;
        }
    }
}
