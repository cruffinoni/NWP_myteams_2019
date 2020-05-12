/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER
#define SRC_MYTEAMS_SERVER

#include "socket.h"
#include "client.h"

typedef struct server_s {
    int socket;
    client_t *client[MAX_CONNECTION];
} server_t;


#endif
