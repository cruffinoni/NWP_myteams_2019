/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_CODES
#define SRC_MYTEAMS_CODES

#define _EOF "\r\n"

typedef enum codes_error_e {
    NOT_CONNECTED = 500,
} codes_error_t;

typedef enum codes_legal_e {
    SERVICE_READY = 200,
} codes_legal_t;

typedef unsigned short codes_t;

typedef struct codes_data_s {
    const codes_t code;
    const char *definition;
} codes_data_t;

static const codes_data_t CODES_DATA[] = {
    {NOT_CONNECTED, "The client is not connected"},
    {SERVICE_READY, "Connection established"},
    {0, NULL}
};

const char *get_code_definition(const codes_t code);

#endif
