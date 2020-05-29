/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_CLIENT
#define SRC_MYTEAMS_CLIENT

#include <stdint.h>
#include <uuid/uuid.h>
#include "uid.h"

#define MAX_NAME_LENGTH         32
#define MAX_DESCRIPTION_LENGTH  255
#define MAX_BODY_LENGTH         512
#define MAX_REQUEST_LENGTH      255

enum client_flag_e {
    CLIENT_NONE        = 0u,
    CLIENT_CONNECTED   = 0b1u,
};
typedef unsigned short client_flag_t;

typedef enum client_context_type_e {
    TEAM,
    CHANNEL,
    THREAD,
    INVALID,
    MAX = INVALID,
} client_context_type_t;
typedef uuid_t client_contexts_t[MAX];

typedef struct client_s {
    char name[MAX_NAME_LENGTH];
    uuid_t id;
    int socket;
    client_flag_t flags;
    client_contexts_t context;
} client_t;

#define IS_CONNECTED(c) ((c->flags & CLIENT_CONNECTED) == CLIENT_CONNECTED)

#endif
