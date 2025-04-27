NAME = minishell

SRC_NAME =	main \
			init \
			signals \
			heredoc_signal

BUILDIN_NAME =	ft_cd \
				ft_env \
				ft_exit \
				ft_export \
				ft_pwd \
				ft_unset \
				ft_echo

PARSE_NAME =	unique_quote \
				error_management \
				successive_redirect \
				get_list_args \
				put_full_path \
				to_pipe \
				parse_redir \
				token_at_last \
				expand \
				expand_utils \
				expand_utils2 \
				remove_quote \
				heredoc \
				delete_tmp \
				heredoc_utils \
				heredoc_utils2

UTILS_NAME =	get_env \
				free_list \
				is_special \
				convert_args_to_tab \
				convert_env_export \
				get_entry \
				free_pipe \
				write_error \
				free_data \
				count_argv \


EXEC_NAME =		execute_command \
				redirection \
				redirection2 \
				exec_builtin \
				fd_management \
				exec_pipe \
				execute_command_utils
				

PATH_HANDLER_NAME =	get_full_path \
				
SRC_PATH = src/

BUILDIN_PATH = builtin/

PARSE_PATH = parse/

LIBFT_PATH = libft/

UTILS_PATH = utils/

EXEC_PATH = exec/

PATH_HANDLER_PATH = path_handler/

LIBFT = $(LIBFT_PATH)libft.a

SRC = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_NAME)))

BUILDIN = $(addprefix $(BUILDIN_PATH), $(addsuffix .c, $(BUILDIN_NAME)))

PARSE = $(addprefix $(PARSE_PATH), $(addsuffix .c, $(PARSE_NAME)))

UTILS = $(addprefix $(UTILS_PATH), $(addsuffix .c, $(UTILS_NAME)))

PATH_HANDLER = $(addprefix $(PATH_HANDLER_PATH), $(addsuffix .c, $(PATH_HANDLER_NAME)))

EXEC = $(addprefix $(EXEC_PATH), $(addsuffix .c, $(EXEC_NAME)))

OBJ_PATH = obj/

OBJ_SRC = $(addprefix $(OBJ_PATH)$(SRC_PATH), $(addsuffix .o, $(SRC_NAME)))

OBJ_BUILDIN = $(addprefix $(OBJ_PATH)$(BUILDIN_PATH), $(addsuffix .o, $(BUILDIN_NAME)))

OBJ_PARSE = $(addprefix $(OBJ_PATH)$(PARSE_PATH), $(addsuffix .o, $(PARSE_NAME)))

OBJ_UTILS = $(addprefix $(OBJ_PATH)$(UTILS_PATH), $(addsuffix .o, $(UTILS_NAME)))

OBJ_PATH_HANDLER = $(addprefix $(OBJ_PATH)$(PATH_HANDLER_PATH), $(addsuffix .o, $(PATH_HANDLER_NAME)))

OBJ_EXEC = $(addprefix $(OBJ_PATH)$(EXEC_PATH), $(addsuffix .o, $(EXEC_NAME)))

OBJ = $(OBJ_SRC) $(OBJ_BUILDIN) $(OBJ_PARSE) $(OBJ_UTILS) $(OBJ_PATH_HANDLER) $(OBJ_EXEC)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g 

CLINKS = -lreadline

SUB_DIR = 	$(OBJ_PATH)$(BUILDIN_PATH) $(OBJ_PATH)$(EXEC_PATH) $(OBJ_PATH)$(PARSE_PATH) \
			$(OBJ_PATH)$(PATH_HANDLER_PATH) $(OBJ_PATH)$(SRC_PATH) $(OBJ_PATH)$(UTILS_PATH)

all : make_dirs $(NAME)

make_dirs :
	mkdir -p $(OBJ_PATH) $(SUB_DIR)

$(OBJ_PATH)$(SRC_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(UTILS_PATH)%.o : $(UTILS_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(EXEC_PATH)%.o : $(EXEC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)$(BUILDIN_PATH)%.o : $(BUILDIN_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(PARSE_PATH)%.o :$(PARSE_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(PATH_HANDLER_PATH)%.o : $(PATH_HANDLER_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(BUILDIN) $(PARSE) $(UTILS)  $(PATH_HANDLER) $(EXEC) $(LIBFT) $(CLINKS) -g

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)


clean :
	rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) fclean

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: re all clean fclean make_dirs
