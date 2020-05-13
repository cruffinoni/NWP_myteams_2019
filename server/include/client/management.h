/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_CLIENT_
#define SRC_MYTEAMS_SERVER_CLIENT_

#include "error.h"
#include "client.h"

void free_client(client_t **this);
uerror_t create_client(const int socket, client_t **this);

#endif
