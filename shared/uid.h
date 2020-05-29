/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SHARED_UID
#define SRC_MYTEAMS_SHARED_UID

#define UUID_MAX_NAME (37)
typedef char uuid_name_t[UUID_MAX_NAME];
char *uid_to_string(const uuid_t id);

#endif
