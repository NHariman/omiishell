# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nhariman <nhariman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 23:42:48 by nhariman      #+#    #+#                  #
#    Updated: 2020/12/20 21:58:07 by nhariman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COMPILE = gcc
# COMPILE = clang

FLAGS = -Wall -Werror -Wextra

MINISHELL =		main.c \
				srcs/main/get_next_line.c \
				srcs/main/main_parser.c \
				srcs/main/gen_functions.c \
				srcs/main/ft_argv.c \
				srcs/main/ft_prompts.c \
				srcs/main/dollar_sign.c \
				srcs/main/ft_skip_redirections.c \
				srcs/quotations/ft_skip_quotes.c \
				srcs/quotations/quotation_handler.c \
				srcs/quotations/quotations_parser.c \
				srcs/quotations/no_quotations_parser.c \
				srcs/subparsers/ft_get_rdin.c \
				srcs/subparsers/ft_invalid_line.c \
				srcs/subparsers/ft_make_prompts.c \
				srcs/pipe/ft_pipe_splitter.c \
				srcs/echo/ft_echo.c \
				srcs/cd/ft_cd.c \
				srcs/pwd/ft_pwd.c \
				srcs/env/env.c \
				srcs/exit/exit.c \
				srcs/free/free.c \
				srcs/execv/ft_execv.c \
				srcs/execv/ft_is_directory.c \
				srcs/execv/ft_make_array.c \
				srcs/execv/ft_preprocessor.c \
				srcs/export/ft_export.c \
				srcs/export/ft_add_backslash.c \
				srcs/export/ft_format_export.c \
				srcs/export/ft_sort_env.c \
				srcs/export/ft_update_env.c \
				srcs/unset/ft_unset.c

ECHO =			srcs/echo/echo.c\
				srcs/echo/check_nflag.c\
				srcs/echo/ft_add_enviorment.c\
				srcs/echo/ft_clean_echo.c\
				srcs/echo/ft_get_variable.c\
				srcs/echo/ft_skip_character.c\
				srcs/rd/rd_check.c\
				srcs/rd/rd_set_value.c\
				srcs/rd/re_direct.c\
				srcs/rd/rd_loop.c

OMINISHELL = 	$(MINISHELL:.c=.o)

OECHO =			$(ECHO:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OMINISHELL) $(OECHO) srcs/libft/libft.a
	@$(COMPILE) $(OMINISHELL) $(OECHO) -g -fsanitize=address srcs/libft/libft.a -o $@
	@chmod 311 ./minishell

srcs/libft/libft.a:
	@cd srcs/libft && $(MAKE)

%.o: %.c srcs/minishell.h srcs/yusha.h srcs/niks.h
	@$(COMPILE) -c $(FLAGS) -o $@ -c $<

clean:
	@$(RM) $(OECHO) $(OMINISHELL)
	@cd srcs/libft && $(MAKE) clean

fclean: clean
	@$(RM) $(NAME)
	@cd srcs/libft && $(MAKE) fclean

re: fclean all

test: re
	./minishell

leaks: fclean $(OMINISHELL) $(OECHO) srcs/libft/libft.a
	@$(COMPILE) $(OMINISHELL) $(OECHO) srcs/libft/libft.a -o minishell
	./minishell