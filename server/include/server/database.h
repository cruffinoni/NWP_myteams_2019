/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_DATABASE_
#define SRC_MYTEAMS_SERVER_DATABASE_

#include <uuid/uuid.h>

#define DB_PATH "./database/"
#define DB_USER_PATH DB_PATH "users/"
#define DB_USER_INFO_FILE_PATH     DB_USER_PATH "%s/.info"

typedef struct db_user_list_s {
    client_t client;
    struct db_user_list_s *next;
} db_user_list_t;

bool db_user_exists(const client_t *client);
uerror_t db_create_user(const client_t *client);
uerror_t db_get_user_infos(const char *id, client_t *dest);
uerror_t db_get_all_users(db_user_list_t **dest);
void db_destroy_user_list(db_user_list_t *header);

uerror_t read_user_info_file(const char *folder_name, client_t *dest);

#endif
