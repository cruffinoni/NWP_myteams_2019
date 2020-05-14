/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_ERROR_
#define SRC_ERROR_

#include <stdarg.h>

typedef unsigned int uerror_t;

enum error_e {
    ERR_NONE = 0,
    ERR_MALLOC,
    ERR_INVALID_ARG_COUNT,
    ERR_EXIT_HELP,
    ERR_INVALID_ARG,
    ERR_PORT_NOT_NUMBER,
    ERR_INTERNAL,
    ERR_SOCKET,
    ERR_LOCAL,

    ERR_MAX_ERR,
    ERR_EXIT = 84,
};

uerror_t display_error_message(const uerror_t error);
uerror_t display_perror_internal_(const char *source, const uerror_t code);

#define _1_DISPLAY_PERROR(s)    (display_perror_internal_(s, ERR_INTERNAL))
#define _2_DISPLAY_PERROR(s, c) (display_perror_internal_(s, c))
#define _X_DISPLAY_PERROR(s, c, func, ...) func
#define _DISPLAY_PERROR(...)    _X_DISPLAY_PERROR(__VA_ARGS__, \
                                _2_DISPLAY_PERROR(__VA_ARGS__), \
                                _1_DISPLAY_PERROR(__VA_ARGS__))

#endif
