/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "error.h"

static const char *ERROR_DEFINITION[] = {
    "No error so far",
    "Error malloc, memory exhausted",
    "Too few or to many arguments, rerun with -h or --help flag",
    "USAGE: ./myftp port\n"
    "\t- [port] is the port number on which the server socket will listen\n",
    "Unknown argument detected, rerun with -h or --help flag",
    "The port entered is not a number",
    "Woops! An error occurred...",
    "Internal error occurred during socket creation",
};

uerror_t display_perror_internal_(const char *source, const uerror_t code)
{
    if (errno > sys_nerr - 1) {
        printf("Errno is higher than the fixed limit: %i\n", errno);
        return (code);
    }
    printf("%s: %s", source, strerror(errno));
    return (code);
}

uerror_t display_error_message(const uerror_t error)
{
    if (error >= ERR_MAX_ERR)
        return (ERR_EXIT);
    printf("%s (code %u).\n", ERROR_DEFINITION[error], error);
    return (error == ERR_EXIT_HELP ? ERR_NONE : ERR_EXIT);
}
