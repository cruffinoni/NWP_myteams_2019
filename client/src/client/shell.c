/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** shell.c - file used to handle commands
*/

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "socket.h"
#include "utils.h"
#include "error.h"
#include "client/shell.h"
#include "client/utils.h"
#include "communication/codes.h"

static long get_server_message(socket_t *socket)
{
    char *server_response = get_server_response(socket);
    long status_code;

    if (server_response == NULL)
        return (ERR_INIT);
    status_code = get_status_code(server_response);
    free(server_response);
    return (status_code);
}

static int fetch_stdin(socket_t *socket, char *buffer)
{
    char **user_entry = NULL;

    user_entry = str_to_array(buffer);
    free(buffer);
    if (user_entry == NULL)
        return (ERR_INIT);
    if (tab_len(user_entry) > 0)
        if (process_command(socket, user_entry)) {
            free_char_tab(user_entry);
            return (ERR_INIT);
        }
    free_char_tab(user_entry);
    return (ERR_NONE);
}

static int check_activity(socket_t *params, fd_set *read)
{
    char *buffer = NULL;
    long status_code;

    if (FD_ISSET(STDIN_FILENO, read)) {
        buffer = get_buffer();
        if (buffer == NULL) {
            ACTIVE_SERVER = false;
            return (ERR_NONE);
        }
        if (fetch_stdin(params, buffer) == ERR_INIT)
            return (errno == 0 ? ERR_NONE : ERR_INIT);
    }
    if (FD_ISSET(params->sock_fd, read)) {
        status_code = get_server_message(params);
        if (status_code == SERVICE_CLOSING)
            ACTIVE_SERVER = false;
    }
    return (ERR_NONE);
}

static int get_select(socket_t *params, fd_set *read)
{
    int select_res;

    FD_ZERO(read);
    FD_SET(STDIN_FILENO, read);
    FD_SET(params->sock_fd, read);
    select_res = select(params->sock_fd + 1, read, NULL,
        NULL, NULL);
    return (select_res);
}

int shell(socket_t *params)
{
    int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
    int activity;
    fd_set read;

    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);
    while (ACTIVE_SERVER) {
        print_client_prompt(params);
        activity = get_select(params, &read);
        if (activity < 0)
            return (ERR_INIT);
        if (activity == 0)
            return (ERR_NONE);
        if (check_activity(params, &read) == ERR_INIT)
            return (ERR_INIT);
    }
    return (ERR_NONE);
}
