/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:47 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 17:50:35 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_tok_type type)
{
	if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_REDIR_APP || type == TOK_HEREDOC)
		return (1);
	return (0);
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != TOK_PIPE)
	{
		if (is_redir_token(tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		else if (tmp->type == TOK_WORD)
		{
			count++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (count);
}

t_word	*create_word_node(char *lexeme)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->segs = NULL; 
	(void)lexeme;
	return (word);
}