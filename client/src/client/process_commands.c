/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** process_commands.c - file who take args and execute is proper function
*/

#include <stdio.h>
#include <string.h>
#include "client/commands.h"
#include "utils.h"

void process_command(socket_t *socket, char **args)
{
    str_to_lower_case(args[0]);
    for (int i = 0; i < NBR_FUNCTIONS; ++i) {
        if (strcmp(commands[i], args[0]) == 0) {
            command_functions[i](socket, args);
            return;
        }
    }
    printf("Commande non reconnue : %s\n", args[0]);
}
