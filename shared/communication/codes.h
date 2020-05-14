/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_CODES
#define SRC_MYTEAMS_CODES

#define _EOL "\r\n"

typedef enum codes_error_e {
    NOT_CONNECTED = 500,
    ALREADY_LOGGED,
    INVALID_ARG_COUNT,
    LINE_TOO_LONG,
    COMMAND_NOT_FOUND,
    INTERNAL_ERROR,
} codes_error_t;

typedef enum codes_informative_e {
    SERVICE_CLOSING = 300,
} codes_informative_t;

typedef enum codes_positive_e {
    SERVICE_READY = 200,
    LOGIN_SUCCESSFUL,
    DISCONNECTED,
} codes_positive_t;

typedef unsigned short codes_t;

typedef struct codes_data_s {
    const codes_t code;
    const char *definition;
} codes_data_t;

static const codes_data_t CODES_DATA[] = {
    {NOT_CONNECTED,     "The client is not connected"},
    {ALREADY_LOGGED,    "The client is already logged"},
    {INVALID_ARG_COUNT, "Invalid argument count, got X expected Y"},
    {LINE_TOO_LONG,     "Line too long"},
    {COMMAND_NOT_FOUND, "Command not found"},
    {INTERNAL_ERROR, "Server internal error"},

    {SERVICE_READY,     "Connection established"},
    {LOGIN_SUCCESSFUL,  "Logged successfully <uuid>"},
    {DISCONNECTED,      "Client disconnected from server"},
    {SERVICE_CLOSING,   "Remote service disconnected client"},

    {0, NULL}
};

const char *get_code_definition(const codes_t code);

#endif
