# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 16:31:20 by msnizek           #+#    #+#              #
#    Updated: 2026/03/20 14:47:34 by vgotzlov         ###   ########.fr        #
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
				clean_up.c \
				clean_pipeline.c \
				env_utils.c \
				child_utils.c \
				child.c \
				heredocs.c \
				path.c \
				redirections_utils.c \
				redirections.c \
				signals.c \
				pipes.c \
				executor.c \
				builtin_cd.c \
				builtin_exit.c \
				builtin_export_utils.c \
				builtin_export.c \
				builtin_unset.c \
				builtins_nonstateful.c \
				builtin_dispatch.c \
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