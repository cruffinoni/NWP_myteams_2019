/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "server/database/database.h"

uerror_t add_node(db_listing_t **list, const char name[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH])
{
    db_listing_t *node = malloc(sizeof(db_listing_t));
    char *name_uid;

    if (node == NULL)
        return (_DISPLAY_PERROR("malloc - add_node", ERR_MALLOC));
    memset(node->id, 0, UUID_MAX_NAME);
    memset(node->name, 0, MAX_NAME_LENGTH);
    memset(node->id, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(node->name, name);
    name_uid = db_get_uuid_str(name);
    strcpy(node->id, name_uid);
    if (description != NULL)
        strcpy(node->description, description);
    node->next = *list;
    *list = node;
    return (ERR_NONE);
}

void db_destroy_listing(db_listing_t *header)
{
    db_listing_t *curr = header;
    db_listing_t *next;

    if (header == NULL)
        return;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}
