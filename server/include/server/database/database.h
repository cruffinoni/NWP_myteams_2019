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
#include "server/database/listing.h"
#include "server/database/existence.h"

#define DB_PATH                                 "./server/database/"
#define DB_USER_FOLDER      DB_PATH             "users/"
#define DB_USER_PATH        DB_USER_FOLDER      "%s/"
#define DB_INFO_FILE                            ".info"
#define DB_SUB_FILE                             ".subscribe"
#define DB_TEAM_FOLDER      DB_PATH             "teams/"
#define DB_TEAM_PATH        DB_TEAM_FOLDER      "%s/"
#define DB_CHANNEL_FOLDER   DB_TEAM_PATH        "channel/"
#define DB_CHANNEL_PATH     DB_CHANNEL_FOLDER   "%s/"
#define DB_THREAD_PATH      DB_CHANNEL_PATH     "%s.thread"

// Core functions
uerror_t db_create_user(const client_t *client);
uerror_t db_user_add_sub(const client_t *client, const char *team);
uerror_t db_get_user_infos(const char *id, char dest[MAX_NAME_LENGTH]);
uerror_t db_user_remove_sub(const client_t *client, const char *team);
bool db_user_is_subscribed(const client_t *client, const uuid_t team);
bool db_user_is_subscribed_ss(uuid_name_t id, uuid_name_t team_name);

// Internal DB function
uerror_t read_info_file(const char *folder_name, char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH]);
uerror_t read_info_thread_file(const char *full_path, char name[MAX_NAME_LENGTH],
    char description[MAX_DESCRIPTION_LENGTH]);
bool db_path_exists(const char *path, ...);
char *db_get_uuid_str(const char *str);
uerror_t get_file_content(const int fd, char ***output);

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
    const char thread[MAX_NAME_LENGTH],
    const char description[MAX_DESCRIPTION_LENGTH]);
uerror_t db_create_comment(const client_t *client,
    const char body[MAX_BODY_LENGTH]);

#endif
