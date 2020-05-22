/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_DATABASE_
#define SRC_MYTEAMS_SERVER_DATABASE_

#include <stdbool.h>
#include <uuid/uuid.h>
#include "error.h"
#include "client.h"

#define DB_PATH                         "./database/"
#define DB_USER_FOLDER DB_PATH "users/"
#define DB_USER_PATH DB_USER_FOLDER            "%s/"
#define DB_INFO_FILE                    ".info"
#define DB_TEAM_PATH DB_PATH            "teams/%s/"
#define DB_CHANNEL_FOLDER DB_TEAM_PATH    "channel/"
#define DB_CHANNEL_PATH DB_TEAM_PATH    "channel/%s/"
#define DB_THREAD_PATH DB_CHANNEL_PATH  "%s.thread"

typedef struct db_user_list_s {
    client_t client;
    struct db_user_list_s *next;
} db_listing_t;


// Core functions
uerror_t db_create_user(const client_t *client);
uerror_t db_get_user_infos(const char *id, client_t *dest);
bool db_user_exists(const client_t *client);
bool db_user_exists_str(const char *id);
bool db_team_exists(const uuid_t team);
bool db_team_exists_str(const char *team);
bool db_channel_exists(const uuid_t team, const uuid_t channel);
bool db_channel_exists_str(const uuid_t team, const char *channel);
bool db_thread_exists_str(const uuid_t team, const uuid_t channel,
    const char *thread);
bool db_thread_exists(const uuid_t team, const uuid_t channel,
    const uuid_t thread);

// Users functions
uerror_t db_get_all_users(db_listing_t **dest);

// Internal DB function
uerror_t read_user_info_file(const char *folder_name, client_t *dest);
bool db_path_exists(const char *path, ...);
char *db_get_uuid_str(const char *str);
uerror_t add_node(db_listing_t **list, client_t *buffer);
void db_destroy_listing(db_listing_t *header);

// Private message functions
uerror_t db_send_pm(const client_t *src, const char *dest_id, const char *msg);
uerror_t db_get_all_message(const uuid_t author, const char *dest,
    char **buffer);

// Team DB function
uerror_t db_create_team(const char team[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH]);
uerror_t db_create_channel(const uuid_t team,
    const char channel[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH]);
uerror_t db_create_thread(const client_t *client,
    const char channel[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH]);
uerror_t db_create_comment(uuid_t client, client_contexts_t ctx,
    const char body[MAX_BODY_LENGTH]);

#endif
