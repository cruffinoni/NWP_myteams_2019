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

#define DB_PATH "./database/"
#define DB_USER_PATH DB_PATH "users/"
#define DB_USER_INFO_FILE_PATH     DB_USER_PATH "%s/.info"

typedef struct db_user_list_s {
    client_t client;
    struct db_user_list_s *next;
} db_user_list_t;


// Core functions
bool db_user_exists(const client_t *client);
uerror_t db_create_user(const client_t *client);
uerror_t db_get_user_infos(const char *id, client_t *dest);
bool db_user_exists_id(const char *id);

// Users functions
uerror_t db_get_all_users(db_user_list_t **dest);
void db_destroy_user_list(db_user_list_t *header);

// Internal DB function
uerror_t read_user_info_file(const char *folder_name, client_t *dest);


// Private message functions
uerror_t db_send_pm(const client_t *src, const char *dest_id, const char *msg);
uerror_t db_get_all_message(const uuid_t author, const char *dest,
    char **buffer);

#endif
