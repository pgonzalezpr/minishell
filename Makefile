NAME = minishell

SRCS =  ./srcs/minishell.c ./srcs/build.c ./srcs/exec.c									\
		./srcs/clean.c  ./srcs/builtins/echo.c 											\
		./srcs/builtins/env.c ./srcs/builtins/pwd.c     								\
		./srcs/builtins/unset.c ./srcs/builtins/export.c ./srcs/pipes.c					\
		./srcs/utils.c ./srcs/tokenize.c ./srcs/expand.c ./srcs/exec_utils.c			\
		./srcs/str_utils.c ./srcs/print.c ./srcs/builtins/check_builtin.c ./srcs/path.c	\
		./srcs/builtins/utils_env_2.c ./srcs/builtins/utils_env.c						\
		./srcs/builtins/exit.c ./srcs/builtins/cd.c ./srcs/builtins/cd_utils.c 			\
		./srcs/signals/signal.c	./srcs/tokenize_utils.c

INCLUDE = ./libft/libft.h ./include/minishell.h

LIBFT_DIR = libft
READLINE_DIR = include/readline

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD -g

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "$(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"

OBJS = ${SRCS:.c=.o}
DEPS = $(addsuffix .d, $(basename $(SRCS)))

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT_DIR}/libft.a $(INCLUDE) Makefile 
	@${CC} ${OBJS} -L${LIBFT_DIR} -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -lreadline -lft -o ${NAME}
	@echo "\n$(RED) Created $(NAME) ✓ $(DEF_COLOR)\n"

$(LIBFT_DIR)/libft.a:
	@make bonus -C $(LIBFT_DIR)

$(READLINE_DIR)/libreadline.a $(READLINE_DIR)/libhistory.a:
	@./configure
	@make -C $(READLINE_DIR) > /dev/null

-include ${DEPS}

clean:
	@${RM} ${OBJS}
	@${RM} ${DEPS}
	@make clean -C $(LIBFT_DIR)
	@echo "\n$(DARK_YELLOW) Removed all objects$(DEF_COLOR)\n"

fclean: 
	@${RM} ${OBJS}
	@${RM} ${DEPS}
	@${RM} ${NAME}
	@make fclean -C $(LIBFT_DIR)
	@echo "\n$(DARK_YELLOW)Removed all objects and executable$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
