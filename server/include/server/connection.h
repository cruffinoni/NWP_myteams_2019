/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_CONNECTION
#define SRC_MYTEAMS_SERVER_CONNECTION

#include <errno.h>

#define IS_ERRNO_MANAGEABLE(c) (c == ECONNRESET || c == ENOTCONN || \
                                c == ETIMEDOUT)

uerror_t run_server(server_t *this);

#endif
