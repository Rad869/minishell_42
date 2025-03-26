NAME = minishell

SRC_NAME =	main \

BUILDIN_NAME =

PARSE_NAME =	unique_quote \
				error_management \
				successive_redirect \

SRC_PATH = src/

BUILDIN_PATH = buildin/

PARSE_PATH = parse/

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

SRC = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_NAME)))

BUILDIN = $(addprefix $(BUILDIN_PARH), $(addsuffix .c, $(BUILDIN_NAME)))

PARSE = $(addprefix $(PARSE_PATH), $(addsuffix .c, $(PARSE_NAME)))

OBJ_PATH = obj/

OBJ_SRC = $(addprefix $(OBJ_PATH)src/, $(addsuffix .o, $(SRC_NAME)))

OBJ_BUILDIN = $(addprefix $(OBJ_PATH)buildin/, $(addsuffix .o, $(BUILDIN_NAME)))

OBJ_PARSE = $(addprefix $(OBJ_PATH)parse/, $(addsuffix .o, $(PARSE_NAME)))

OBJ = $(OBJ_SRC) $(OBJ_BUILDIN) $(OBJ_PARSE)

CC = cc

CFLAGS = -Wall -Wextra -Werror

CLINKS = -lreadline

$(OBJ_PATH)$(SRC_PATH)%.o : $(SRC) $(BUILDIN) $(PARSE) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $^ $(CLINKS)

$(OBJ_PATH)$(BUILDIN_PATH)%.o : $(SRC) $(BUILDIN) $(PARSE) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $^ $(CLINKS)

$(OBJ_PATH)$(PARSE_PATH)%.o : $(SRC) $(BUILDIN) $(PARSE) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $^ $(CLINKS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) libft/libft.a

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(BUILDIN) $(PARSE) $(LIBFT) $(CLINKS) -g

all : $(NAME) 

clean :
	rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean : clean
	rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re : fclean all

.PHONY: re all clean fclean
