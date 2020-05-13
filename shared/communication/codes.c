/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include "codes.h"

const char *get_code_definition(const codes_t code)
{
    for (int i = 0; CODES_DATA[i].definition != NULL; ++i)
        if (CODES_DATA[i].code == code)
            return (CODES_DATA[i].definition);
    return ("(code nonexistent)");
}
