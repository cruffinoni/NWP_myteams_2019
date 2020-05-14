/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <uuid/uuid.h>
#include "uid.h"

char *uid_to_string(const uuid_t id)
{
    static uuid_name_t name;

    uuid_unparse_lower(id, name);
    return (name);
}
