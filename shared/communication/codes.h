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
    ALREADY_LOGGED = 500,
    INVALID_ARG_COUNT,
    LINE_TOO_LONG,
    COMMAND_NOT_FOUND,
    INTERNAL_ERROR,
    ARGUMENT_TOO_LONG,
    NOT_IMPLEMENTED,
    BODY_TOO_LONG,
    FORBIDDEN,
} codes_error_t;

typedef enum codes_informative_e {
    SERVICE_CLOSING = 300,
    ID_DOESNT_EXISTS,
    ID_ALREADY_EXISTS,
    INVALID_SYNTAX,
    INVALID_ID_PROVIDED,
    TEAM_ALREADY_EXISTS,
    CHANNEL_ALREADY_EXISTS,
    THREAD_ALREADY_EXISTS,
    START_LISTING,
    LISTING,
    END_LISTING,
    NOTIFICATION,
} codes_informative_t;

typedef enum codes_positive_e {
    OK = 200,
    CLIENT_CONTEXT_RESET,
    SERVICE_READY,
    LOGIN_SUCCESSFUL,
    DISCONNECTED,
} codes_positive_t;
typedef unsigned short codes_t;

typedef struct codes_data_s {
    const codes_t code;
    const char *definition;
} codes_data_t;

static const codes_data_t CODES_DATA[] = {
    {ALREADY_LOGGED,         "The client is already logged"},
    {INVALID_ARG_COUNT,      "Invalid argument count, got X expected Y"},
    {LINE_TOO_LONG,          "Line too long"},
    {COMMAND_NOT_FOUND,      "Command not found"},
    {INTERNAL_ERROR,         "Server internal error"},
    {INVALID_SYNTAX,         "One of the parameters provided is invalid"},
    {INVALID_ID_PROVIDED,    "Invalid id provided"},
    {ID_DOESNT_EXISTS,       "The provided unique ID is invalid"},
    {ID_ALREADY_EXISTS,      "The provided unique ID already exists"},
    {ARGUMENT_TOO_LONG,      "One of the provided arguments'"
                             "length is too long"},
    {TEAM_ALREADY_EXISTS,    "The given team's name is already taken"},
    {CHANNEL_ALREADY_EXISTS, "The given channel's name is already taken"},
    {THREAD_ALREADY_EXISTS,  "The given thread's name is already taken"},

    {OK,                     "Command OK"},
    {CLIENT_CONTEXT_RESET,   "Client contexts' has been reset"},
    {SERVICE_READY,          "Connection established"},
    {LOGIN_SUCCESSFUL,       "Logged successfully <uuid>"},
    {DISCONNECTED,           "Client disconnected from server"},
    {SERVICE_CLOSING,        "Remote service disconnected client"},
    {START_LISTING,          "The server is about to start a listing"},
    {END_LISTING,            "End of the listing"},
    {NOT_IMPLEMENTED,        "Command not implemented or partially"},
    {NOTIFICATION,           "Notification received: <?>"},
    {BODY_TOO_LONG,          "The message's length is too long"},
    {FORBIDDEN,              "You don't have the rights to do that"},

    {0, NULL}
};

const char *get_code_definition(const codes_t code);

#endif
