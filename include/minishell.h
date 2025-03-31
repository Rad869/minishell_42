/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:02:54 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 08:12:27 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH_LENGTH 1024
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_list_args
{
	char				*content;
	struct s_list_args	*next;
}	t_list_args;

typedef struct s_general
{
	t_env		*env;
	t_list_args	*args;
	int			last_exit_status;
}	t_general;

/*
*	Error mamagements, Syntaxes error of the input entry
*	Return Value
*	Return 1 if success and 0 either
*/
int				unique_quote(char *line);
int				successive_redirect(char *line);
int				error_management(char	*line);
//---------------------------------Utils------------------------------------
t_env			*get_env(char **env);
void			free_env(t_env *env);
t_list_args		*get_list_args(char *line);
void			free_list_args(t_list_args **args);
int				is_special(char *line);
char			*get_path(t_env *env);
void			double_free(char **argv);
char			*get_full_p(char *env_path, char *cmd);
char			**convert_list_to_char(t_list_args *args);
t_general		*init(char **env_arg);
void			put_full_path(char **cmd, t_general *general);
int				get_entry(t_general *general);


int	execute_command(int argc, char **argv);


int	ft_echo(int argc, char **argv);
int	ft_cd(int argc, char **argv);
int	ft_pwd(int argc, char **argv);
int	ft_export(int argc, char **argv);
int	ft_env(int argc, char **argv);
int	ft_unset(int argc, char **argv);
int	ft_exit(int argc, char **argv);
#endif
