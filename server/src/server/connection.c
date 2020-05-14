/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "server/server.h"
#include "server/connection.h"
#include "client/users.h"
#include "client/commands.h"
#include "utils.h"

static uerror_t process_client_input(server_t *this, const int client,
    char *buffer, const int returned_val)
{
    char **args;
    uerror_t err;

    if (returned_val == MAX_REQUEST_LENGTH)
        return (send_reply(client, LINE_TOO_LONG,
        "The max length of a command line is: %li", MAX_REQUEST_LENGTH));
    args = str_to_array(buffer);
    if (args == NULL)
        return (ERR_MALLOC);
    err = parse_command(this, client, args);
    free_char_tab(args);
    return (err);
}

static uerror_t handle_client_input(server_t *this, const int client_socket)
{
    char buffer[MAX_REQUEST_LENGTH];
    ssize_t rtn;
    uerror_t err = ERR_NONE;

    memset(buffer, 0, MAX_REQUEST_LENGTH);
    rtn = read(client_socket, buffer, MAX_REQUEST_LENGTH);
    if (rtn == -1 && !IS_ERRNO_MANAGEABLE(errno))
        return (_DISPLAY_PERROR("read"));
    else if (rtn == 0 || IS_ERRNO_MANAGEABLE(errno)) {
        if (IS_ERRNO_MANAGEABLE(errno))
            errno = 0;
        disconnect_client(this, client_socket, NULL);
        free_client(&this->client[client_socket]);
        FD_CLR(client_socket, &this->active_fd);
        _PRINT_SERVER("[%i] Disconnected\n", client_socket);
    }
    else
        err = process_client_input(this, client_socket, buffer, rtn);
    return (err);
}

static uerror_t accept_client(server_t *this)
{
    sockaddrin_t client_data;
    socklen_t len = 0;
    int client_socket = accept(this->socket, (sockaddr_t *) &client_data, &len);

    if (client_socket == -1)
        return (_DISPLAY_PERROR("accept"));
    _PRINT_SERVER("[%i] Incoming connection from '%s':'%hd'.\n",
        client_socket, inet_ntoa(client_data.sin_addr),
        ntohs(client_data.sin_port));
    FD_SET(client_socket, &this->active_fd);
    return (create_client(client_socket, &this->client[client_socket]));
}

static uerror_t handle_connection(server_t *this, fd_set *read_fd)
{
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (!FD_ISSET(i, read_fd))
            continue;
        if (i == this->socket)
            return (accept_client(this));
        else
            return (handle_client_input(this, i));
    }
    return (ERR_NONE);
}

uerror_t run_server(server_t *this)
{
    uerror_t err;
    fd_set read_fd;

    FD_ZERO(&read_fd);
    ACTIVE_SERVER = true;
    _PRINT_SERVER("Ready to accept connections...\n");
    while (ACTIVE_SERVER) {
        read_fd = this->active_fd;
        if (select(MAX_CONNECTION, &read_fd, NULL, NULL,
            NULL) < 0 && errno != EINTR)
            return (_DISPLAY_PERROR("select"));
        if (errno == EINTR)
            return (ERR_NONE);
        err = handle_connection(this, &read_fd);
        if (err != ERR_NONE)
            return (err);
    }
    return (ERR_NONE);
}
