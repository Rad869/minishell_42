/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:02:54 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 01:15:31 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH_LENGTH 1024
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_signal
{
	pid_t	child_pid;
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
	struct s_list_args	*prev;
}	t_list_args;

typedef enum e_redir_type
{
	NONE = 0,
	INPUT_REDIR = 1,
	OUTPUT_REDIR = 2,
	OUTPUT_APPEND = 3
}	t_redir_type;

typedef struct s_heredoc
{
	char				*delimiter;
	int					expand;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe
{
	t_list_args		*content;
	t_redir			*redir_list;
	t_heredoc		*heredoc_list;
	int				input_type;
	int				fd[2];
	int				heredoc_fd;
	char			*heredoc_file;
	char			**argv;
	char			**env;
	char			argc;
	pid_t			pid;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_general
{
	t_env		*env;
	t_list_args	*args;
	t_pipe		*pipe_list;
	t_signal	*signal;
	char		*home;
	int			last_exit_status;
	int			default_fd[2];
	int			nbr_cmds;
	int			no_child;
	int			is_parent;
	int			heredoc_file_num;
}	t_general;

int				unique_quote(char *line);
int				successive_redirect(char *line);
int				error_management(char	*line);
int				is_token_at_last(char *line);
t_env			*get_env(char **env);
void			affect_expand_value(char (*value)[5000],
					char *tmp, int *k, int *i);
int				access_output(char *filename);
int				expand_tild(char **line, t_general *g);
void			invalid_option_mess(char *cmd, char *opt);
char			**convert_env_to_char_export(t_env *env);
t_general		*get_general(void);
void			free_env(t_env *env);
void			free_pipe(t_pipe **pipe_list);
t_list_args		*get_list_args(char *line);
void			free_list_args(t_list_args **args);
int				is_special(char *line);
int				is_quote(char c);
void			remove_quote(char **value);
char			*get_path(t_env *env);
void			double_free(char **argv);
char			*get_full_p(char *env_path, char *cmd);
char			**convert_list_to_char(t_list_args *args);
t_general		*init_general(char **env_arg);
t_pipe			*init_pipe(void);
void			put_full_path(char **cmd, t_general *general);
int				get_entry(t_general *general);
int				get_len_word(char *line, int i);
void			add_last_list(t_list_args **list, char *content);
int				to_pipe(t_general *general);
void			remove_elem_list(t_list_args *prev, t_list_args *n,
					t_list_args *value, t_pipe *p);
void			parse_redir(t_pipe **p);
void			expand(char **line, t_general *general);
void			change_expand_pipe(t_pipe *pipe, t_general *general);
void			write_error(char *cmd);
int				all_heredoc(t_general *general);
void			delete_all_tmp(t_general *general);
int				exec_command(t_general *general);
void			free_all(t_general *general);
void			free_data(t_general *general);
int				exec_redirection(t_pipe *pip);
int				count_argv(char **argv);
int				exec_builtin(char **argv, int argc, t_general *general);
int				exec_builtin2(char **argv, int argc, t_general *general);
char			**convert_env_to_char(t_env *env);
char			*get_env_name(char *line);
char			*get_env_value(char *line);
void			fd_management(t_pipe *pip);
void			exec_pipe(t_pipe *pip, t_general *general);
void			exec_one_process(t_general *general, t_pipe *pip);
void			builtins_in_exec(t_general *general, t_pipe *pip);
int				only_builtin(t_general *general, t_pipe *pip);
void			access_error(t_general *general, t_pipe *pip);
void			expande_heredoc(char **line, t_general *general, int flag);
int				is_builtin(char *cmd);
int				loop_heredoc(int fd, char *delimiter, int f);
void			affect_heredoc_name(t_pipe *pip);
void			signals(void);
void			heredoc_signals(void);
void			sigint_handler_main(int signum);
int				signal_message(t_general *general, int sig);
int				ft_echo(int argc, char **argv, t_general *ret);
int				ft_cd(int argc, char **argv, t_general *ret);
int				ft_pwd(int argc, char **argv, t_general *ret);
int				ft_export(int argc, char **argv, t_general *ret);
int				ft_env(int argc, char **argv, t_general *ret);
int				ft_unset(int argc, char **argv, t_general *ret);
int				ft_exit(int argc, char **argv, t_general *ret);

#endif
