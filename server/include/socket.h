/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER_SOCKET
#define SRC_MYTEAMS_SERVER_SOCKET

#include <stdint.h>
#include <limits.h>
#include <netinet/in.h>

typedef struct sockaddr_in sockaddrin_t;
typedef struct sockaddr sockaddr_t;

static const ushort MAX_IP_PORT    = 0xFF;
static const ushort MAX_PORT       = 0xFFFF;
static const int INVALID_SOCKET = -1;

#define MAX_CONNECTION      FD_SETSIZE

#endif
