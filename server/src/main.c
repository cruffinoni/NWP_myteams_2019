/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include "server/server.h"
#include "server/connection.h"

int main(const int ac, const char **av)
{
    server_t *server = NULL;
    uerror_t err = create_server(&server, ac, av);

    if (err != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    err = run_server(server);
    free_server(server);
    return (err != ERR_NONE ? (int) display_error_message(err) : ERR_NONE);
}
