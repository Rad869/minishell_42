/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:02:54 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/02 05:24:18 by rrabeari         ###   ########.fr       */
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
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_signal
{
	pid_t	child_pid;
	int		exit_status;
	int		in_execution;
}	t_signal;

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

typedef enum e_redirect_type
{
	INPUT_REDIRECT =  1,
	OUTPUT_REDIRECT = 2,
	HEREDOC = 3,
	OUTPUT_APPEND = 4
}	t_redirect_type;

typedef struct s_pipe
{
	t_list_args		*content;
	struct s_pipe	*next;
} t_pipe;

typedef struct s_general
{
	t_env		*env;
	t_list_args	*args;
	t_pipe		*pipe_list;
	int			last_exit_status;
	t_signal	*signal;
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
void			free_pipe(t_pipe **pipe_list);
t_list_args		*get_list_args(char *line);
void			free_list_args(t_list_args **args);
int				is_special(char *line);
char			*get_path(t_env *env);
void			double_free(char **argv);
char			*get_full_p(char *env_path, char *cmd);
char			**convert_list_to_char(t_list_args *args);
t_general		*init_general(char **env_arg);
t_pipe			*init_pipe();
void			put_full_path(char **cmd, t_general *general);
int				get_entry(t_general *general);
void			add_last_list(t_list_args **list, char *content);
void			to_pipe(t_general *general);


int	execute_command(int argc, char **argv);


int	ft_echo(int argc, char **argv);
int	ft_cd(int argc, char **argv);
int	ft_pwd(int argc, char **argv);
int	ft_export(int argc, char **argv);
int	ft_env(int argc, char **argv);
int	ft_unset(int argc, char **argv);
int	ft_exit(int argc, char **argv);

//interactive_mode
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		init_signals(t_general *general);
t_general	*get_general_instance(void);
void		set_general_instance(t_general *general);
void		handle_eof(t_general *general);
#endif
