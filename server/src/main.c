/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <signal.h>
#include "server/server.h"
#include "server/connection.h"

void catch_signal(int signal_id)
{
    if (signal_id == SIGINT)
        ACTIVE_SERVER = false;
    else if (signal_id == SIGPIPE)
        _PRINT_SERVER("[!] SIGPIPE caught...\n");
}

int main(const int ac, const char **av)
{
    server_t *server = NULL;
    uerror_t err = create_server(&server, ac, av);

    if (err != ERR_NONE) {
        free_server(server);
        return (display_error_message(err));
    }
    if (setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        free_server(server);
        return (_DISPLAY_PERROR("setvbuf"));
    }
    if (signal(SIGINT, &catch_signal) == SIG_ERR ||
        signal(SIGPIPE, &catch_signal) == SIG_ERR)
        return (_DISPLAY_PERROR("signal"));
    err = run_server(server);
    free_server(server);
    return (err != ERR_NONE ? (int) display_error_message(err) : ERR_NONE);
}
