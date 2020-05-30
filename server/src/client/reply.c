/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "communication/codes.h"
#include "error.h"

uerror_t send_reply(const int client, const codes_t code,
    const char *fmt, ...)
{
    char *reply = NULL;
    char *message = NULL;
    va_list list;

    if (fmt != NULL)  {
        va_start(list, fmt);
        if (vasprintf(&message, fmt, list) < 0) {
            va_end(list);
            return (_DISPLAY_PERROR("vasprintf - send_reply"));
        }
        va_end(list);
    } else if (asprintf(&message, "%s", get_code_definition(code)) < 0)
        return (_DISPLAY_PERROR("asprintf - send_reply"));
    if (asprintf(&reply, "%i: %s" _EOL, code, message) < 0) {
        free(message);
        return (_DISPLAY_PERROR("asprintf - send_reply"));
    }
    write(client, reply, strlen(reply));
    free(reply);
    free(message);
    return (ERR_NONE);
}
