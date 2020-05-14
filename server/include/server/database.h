/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_DATABASE_
#define SRC_MYTEAMS_SERVER_DATABASE_

#define DB_PATH "./database/"
#define DB_USER_PATH DB_PATH "users/"
#define DB_USER_INFO_FILE_PATH     DB_USER_PATH "%s/.info"

bool db_user_exists(const client_t *client);
uerror_t db_create_user(const client_t *client);

#endif
