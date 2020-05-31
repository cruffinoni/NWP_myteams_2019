/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_DATABASE_LISTING
#define SRC_MYTEAMS_DATABASE_LISTING

#include <stdbool.h>
#include <uuid/uuid.h>
#include "error.h"
#include "client.h"

// Listing
typedef struct db_listing_s {
    uuid_name_t id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct db_listing_s *next;
} db_listing_t;

uerror_t add_node(db_listing_t **list, const char name[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH]);
void db_destroy_listing(db_listing_t *header);
uerror_t db_list_teams(db_listing_t **dest);
uerror_t db_list_users(db_listing_t **dest);
uerror_t db_list_channel(db_listing_t **dest, const char *team);
uerror_t db_list_thread(db_listing_t **dest, const client_contexts_t ctx);
uerror_t db_list_comment(db_listing_t **dest, const client_contexts_t ctx);
uerror_t db_display_list(const int client, const char *title,
    const db_listing_t *list);
uerror_t db_list_user_subscription(const client_t *user);
uerror_t db_list_team_subscriber(const int client, const uuid_name_t team_id);

#endif
