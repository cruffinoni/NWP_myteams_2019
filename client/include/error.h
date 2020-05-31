/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** error.h
*/

#ifndef NWP_MYTEAMS_2019_ERROR_H
#define NWP_MYTEAMS_2019_ERROR_H

#include "socket.h"

#define ERR_NONE    0
#define EOF_D       1
#define ERR_INIT    84

void free_params(socket_t *params);

#endif