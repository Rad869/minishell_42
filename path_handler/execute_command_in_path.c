/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_in_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:08:29 by cramaros          #+#    #+#             */
/*   Updated: 2025/02/08 10:08:58 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_command_in_path(int argc, char *argv[])
{
    if (argc < 1)
        return 0;
    const char *command = argv[0];

    if (strcmp(command, "exit") == 0) 
        execute_builtin_exit();

    if (is_absolute_path(command))
        return execute_absolute_command(command, argv);

    return find_command_in_path(command, argv);
}

