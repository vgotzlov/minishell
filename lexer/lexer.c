/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:11:36 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/04/08 23:47:06 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word(char *line, int *i, t_token **head)
{
	int		w_len;
	char	*w_str;
	t_quote	q;

	w_len = get_word_length(line, *i, &q);
	if (w_len == -1)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (-1);
	}
	w_str = ft_substr(line, *i, w_len);
	add_token_back(head, create_token(TOK_WORD, w_str, q));
	*i += w_len;
	return (0);
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line && line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (handle_operator(line, &i, &head))
			continue ;
		if (handle_word(line, &i, &head) == -1)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
