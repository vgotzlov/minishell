/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:56:19 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 13:56:51 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_op(t_token **head, t_tok_type type, char *val, int step)
{
	int	*i;

	add_token_back(head, create_token(type, ft_strdup(val), Q_NONE));
	*i += step;
	return (1);
}

int	handle_operator(char *line, int *i, t_token **head)
{
	if (line[*i] == '|')
		return (append_op(head, TOK_PIPE, "|", 1, i));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return (append_op(head, TOK_HEREDOC, "<<", 2, i));
	else if (line[*i] == '<')
		return (append_op(head, TOK_REDIR_IN, "<", 1, i));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return (append_op(head, TOK_REDIR_APP, ">>", 2, i));
	else if (line[*i] == '>')
		return (append_op(head, TOK_REDIR_OUT, ">", 1, i));
	return (0);
}
