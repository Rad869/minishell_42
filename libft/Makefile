NAME = libft.a

FILE = ft_strlen \
			 ft_memcpy \
			 ft_strlcpy \
			 ft_split \
			 ft_strlcat \
			 ft_isalpha \
			 ft_isdigit \
			 ft_isalnum \
			 ft_isascii \
			 ft_isprint \
			 ft_memset \
			 ft_bzero \
			 ft_toupper \
			 ft_tolower \
			 ft_strchr \
			 ft_strrchr \
			 ft_strncmp \
			 ft_memchr \
			 ft_memcmp \
			 ft_strnstr \
			 ft_strcmp \
			 ft_atoi \
			 ft_memmove \
			 ft_calloc \
			 ft_strdup \
			 ft_substr \
			 ft_strjoin \
			 ft_strtrim \
			 ft_itoa \
			 ft_strmapi \
			 ft_striteri \
			 ft_putchar_fd \
			 ft_putstr_fd \
			 ft_putendl_fd \
			 ft_putnbr_fd \
			 get_next_line

FILEBONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \

OBJSBONUS = $(FILEBONUS:.c=.o)

OBJS = $(FILE:%=%.o)

SRC = $(FILE:%=%.c)

HDR = libft.h

all: $(NAME)

$(NAME): $(SRC)
	@cc -c -Wall -Wextra -Werror $(SRC)
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@stty sane

clean:
	@rm -f $(OBJS) $(OBJSBONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

objbonus: $(FILEBONUS)
	cc -c -Wall -Wextra - Werror $(FILEBONUS)

bonus: $(OBJS) $(OBJSBONUS)
	ar -rc $(NAME) $(OBJS) $(OBJSBONUS)
	ranlib $(NAME)
