NAME = minishell

SRC_NAME =	main \
			init

BUILDIN_NAME =

PARSE_NAME =	unique_quote \
				error_management \
				successive_redirect \
				get_list_args \
				put_full_path \

UTILS_NAME =	get_env \
				free_list \
				is_special \
				convert_args_to_tab \
				get_entry

PATH_HANDLER_NAME =	get_full_path \
				

SRC_PATH = src/

BUILDIN_PATH = buildin/

PARSE_PATH = parse/

LIBFT_PATH = libft/

UTILS_PATH = utils/

PATH_HANDLER_PATH = path_handler/

LIBFT = $(LIBFT_PATH)libft.a

SRC = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_NAME)))

BUILDIN = $(addprefix $(BUILDIN_PARH), $(addsuffix .c, $(BUILDIN_NAME)))

PARSE = $(addprefix $(PARSE_PATH), $(addsuffix .c, $(PARSE_NAME)))

UTILS = $(addprefix $(UTILS_PATH), $(addsuffix .c, $(UTILS_NAME)))

PATH_HANDLER = $(addprefix $(PATH_HANDLER_PATH), $(addsuffix .c, $(PATH_HANDLER_NAME)))

OBJ_PATH = obj/

OBJ_SRC = $(addprefix $(OBJ_PATH)$(SRC_PATH), $(addsuffix .o, $(SRC_NAME)))

OBJ_BUILDIN = $(addprefix $(OBJ_PATH)$(BUILDIN_PATH), $(addsuffix .o, $(BUILDIN_NAME)))

OBJ_PARSE = $(addprefix $(OBJ_PATH)$(PARSE_PATH), $(addsuffix .o, $(PARSE_NAME)))

OBJ_UTILS = $(addprefix $(OBJ_PATH)$(UTILS_PATH), $(addsuffix .o, $(UTILS_NAME)))

OBJ_PATH_HANDLER = $(addprefix $(OBJ_PATH)$(PATH_HANDLER_PATH), $(addsuffix .o, $(PATH_HANDLER_NAME)))

OBJ = $(OBJ_SRC) $(OBJ_BUILDIN) $(OBJ_PARSE) $(OBJ_UTILS) $(OBJ_PATH_HANDLER)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g 

CLINKS = -lreadline

all : $(NAME)

$(OBJ_PATH)$(SRC_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(UTILS_PATH)%.o : $(UTILS_PATH)%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(BUILDIN_PATH)%.o : $(BUILDIN_PATH)%.c 
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(PARSE_PATH)%.o :$(PARSE_PATH)%.c 
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_PATH)$(PATH_HANDLER_PATH)%.o : $(PATH_HANDLER_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(BUILDIN) $(PARSE) $(UTILS)  $(PATH_HANDLER) $(LIBFT) $(CLINKS) -g

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)


clean :
	rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) fclean

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: re all clean fclean
