/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** forbidden.c
*/

#include "error.h"
#include "client/commands.h"
#include "myteams/logging_client.h"

int forbidden(socket_t _UNUSED_ *params, char _UNUSED_ *server_response)
{
    if (client_error_unauthorized() == -1)
        return (ERR_INIT);
    return (ERR_NONE);
}