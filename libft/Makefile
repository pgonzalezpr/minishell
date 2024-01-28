NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./
LIB = ar rcs
RM = rm -f

SRC	=	ft_atoi.c ft_putendl_fd.c ft_strncmp.c \
		ft_bzero.c ft_putnbr_fd.c ft_strnstr.c \
		ft_calloc.c ft_putstr_fd.c ft_strrchr.c \
		ft_isalnum.c  ft_split.c ft_strtrim.c \
		ft_isalpha.c ft_strchr.c ft_substr.c \
		ft_isascii.c ft_strdup.c ft_tolower.c \
		ft_isdigit.c ft_memchr.c ft_striteri.c ft_toupper.c \
		ft_isprint.c ft_memcmp.c ft_strjoin.c \
		ft_itoa.c ft_memcpy.c ft_strlcat.c \
		ft_memmove.c ft_strlcpy.c  ft_memset.c \
		ft_strlen.c ft_putchar_fd.c ft_strmapi.c ft_printf_bonus.c \
		buff_utils_bonus.c build_str_bonus.c build_utils_bonus.c \
		conversion_bonus.c parse_utils_bonus.c get_next_line_bonus.c

BONUSF = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		 ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 

HEADERS = libft.h

SRC_OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUSF:.c=.o)

all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(LIB) $(NAME) $(SRC_OBJ)

bonus: $(SRC_OBJ) $(BONUS_OBJ)
	$(LIB) $(NAME) $(SRC_OBJ) $(BONUS_OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRC_OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re bonus
