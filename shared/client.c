/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "client.h"

void generate_id_from_name(client_t *client)
{
    uuid_generate_md5(client->id, client->id, client->name, MAX_NAME_LENGTH);
}
