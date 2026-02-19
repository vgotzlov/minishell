# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 15:27:15 by msnizek           #+#    #+#              #
#    Updated: 2025/09/10 15:17:57 by msnizek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   := libft.a
CC     := cc
CFLAGS := -Wall -Wextra -Werror -I.

SRC := \
  ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c ft_isalpha.c \
  ft_atoi.c ft_strlen.c ft_strlcat.c ft_strncmp.c ft_strdup.c ft_calloc.c ft_memcpy.c ft_strchr.c \
  ft_strrchr.c ft_strnstr.c ft_bzero.c ft_memchr.c ft_memcmp.c ft_memset.c ft_memmove.c ft_strlcpy.c \
  ft_itoa.c ft_strjoin.c ft_striteri.c ft_strmapi.c ft_split.c ft_substr.c ft_strtrim.c \
  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
  ft_print_characters.c ft_print_numbers.c ft_printf.c \
  get_next_line.c ft_lstnew.c ft_lstadd_front.c \
  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
  ft_lstiter.c ft_lstmap.c ft_lstsize.c ft_lstlast.c \

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
