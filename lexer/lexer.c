/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:11:36 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 14:37:11 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;
	int		w_len;
	char	*w_str;
	t_quote	q;

	head = NULL;
	i = 0;
	while (line && line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (handle_operator(line, &i, &head))
			continue ;
		w_len = get_word_length(line, i, &q);
		if (w_len == -1)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
			free_tokens(head);
			return (NULL);
		}
		w_str = ft_substr(line, i, w_len);
		add_token_back(&head, create_token(TOK_WORD, w_str, q));
		i += w_len;
	}
	return (head);
}

