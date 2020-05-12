/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include "server.h"

int main(const int ac, const char **av)
{
    server_t *server = NULL;
    uerror_t err = create_server(&server, ac, av);

    if (err != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    free_server(server);
    return (0);
}
