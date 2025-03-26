/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:39:45 by cramaros          #+#    #+#             */
/*   Updated: 2025/02/08 10:26:13 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_absolute_path(const char *command)
{
    return command != NULL && command[0] == '/';
}
int execute_absolute_command(const char *command, char *argv[])
{
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork failed");
        return -1;
    }
    if (pid == 0)
    {
        execv(command, argv);
        perror("execv failed");
        exit(1);
    } else
        wait(NULL);
    return 0;
}
int search_directory(const char *dir, const char *command, char *argv[])
{
    DIR *dp = opendir(dir);
    if (dp == NULL)
        return -1;

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) 
    {
        if (ft_strcmp(entry->d_name, command) == 0) 
        {
            char full_path[MAX_PATH_LENGTH];
            snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", dir, command);
            if (access(full_path, X_OK) == 0) 
            {
                closedir(dp);
                return execute_absolute_command(full_path, argv);
            }
        }
    }
    closedir(dp);
    return -1;
}

int find_command_in_path(const char *command, char *argv[])
{
    char *path = getenv("PATH");
    if (path == NULL) 
    {
        printf("Error: PATH is not defined.\n");
        return -1;
    }
    char path_copy[MAX_PATH_LENGTH];
    ft_strncpy(path_copy, path, MAX_PATH_LENGTH);

    char *dir = strtok(path_copy, ":");

    while (dir != NULL) 
    {
        if (search_directory(dir, command, argv) == 0)
            return 0;
        dir = strtok(NULL, ":");
    }
    printf("Error: command not found: %s\n", command);
    return -1;
}
