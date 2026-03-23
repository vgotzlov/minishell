# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 16:31:20 by msnizek           #+#    #+#              #
#    Updated: 2026/03/23 12:38:07 by msnizek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I.
LDFLAGS	= -Llibft -lft -lreadline

SRC			=	lexer/lexer_operators.c \
				lexer/lexer_utils.c \
				lexer/lexer_words.c \
				lexer/lexer.c \
				lexer/token_utils.c \
				parser/segment_handlers.c \
				parser/segment_utils.c \
				parser/segmenter.c \
				parser/parser_args.c \
				parser/parser_cmd.c \
				parser/parser_redirs.c \
				parser/parser_utils.c \
				parser/parser.c \
				expander/expander_utils.c \
				expander/expander.c \
				executor/clean_up.c \
				executor/clean_pipeline.c \
				executor/env_utils.c \
				executor/child_utils.c \
				executor/child.c \
				executor/heredocs.c \
				executor/path.c \
				executor/redirections_utils.c \
				executor/redirections.c \
				executor/signals.c \
				executor/pipes.c \
				executor/executor.c \
				builtins/builtin_cd.c \
				builtins/builtin_exit.c \
				builtins/builtin_export_utils.c \
				builtins/builtin_export.c \
				builtins/builtin_unset.c \
				builtins/builtins_nonstateful.c \
				builtins/builtin_dispatch_utils.c \
				builtins/builtin_dispatch.c \
				main.c \

OBJ			= $(SRC:.c=.o)
LIBFT		= libft/libft.a
HEADER		= minishell.h

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re