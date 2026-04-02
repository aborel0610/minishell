NAME = minishell

CC = cc
LFLAGS = -lreadline
CFLAGS = -g -Wall -Werror -Wextra
LIBFT = ./includes/libft/libft.a
INCLUDE = -I./includes
SRC_DIR = srcs/
OBJ_DIR = objs/

SRCS = srcs/echo.c srcs/cd_pwd_env.c srcs/cleanup.c srcs/unset.c srcs/exit.c srcs/init_new_env.c srcs/IO.c srcs/token_cont.c srcs/token_recognition.c srcs/token_utils.c srcs/main.c srcs/parse_exec.c srcs/free_utils.c srcs/signals.c srcs/build_cmd_struct.c srcs/pipes.c srcs/pipes_utils.c srcs/expansion.c srcs/expansion_cont.c srcs/heredocs.c srcs/errors.c srcs/export.c srcs/env_build.c srcs/exec_builtin.c srcs/savecwd.c srcs/dup2s.c srcs/modified_split.c srcs/cmd_utils.c srcs/builtin_utils.c srcs/export_utils.c srcs/mod_strchr.c srcs/heredocs_utils.c srcs/pipes_cont.c srcs/signals_cont.c srcs/parse_exec_cont.c srcs/token_arg.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):  $(LIBFT) $(OBJS)
	$(CC) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
$(LIBFT):
	$(MAKE) bonus -C ./includes/libft
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
clean:
	$(MAKE) clean -C ./includes/libft
	rm -f $(OBJS)
fclean: clean
	$(MAKE) fclean -C ./includes/libft
	rm -f $(NAME)
re : fclean all

.PHONY: all clean fclean re
