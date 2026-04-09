/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:56:19 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/04/08 23:47:50 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create a new token for operator
static int	append_op(t_token **head, t_tok_type type, char *val)
{
	t_token	*token;
	char	*lexeme;

	lexeme = ft_strdup(val);
	if (!lexeme)
		return (0);
	token = create_token(type, lexeme, Q_NONE);
	if (!token)
	{
		free(lexeme);
		return (0);
	}
	add_token_back(head, token);
	return (1);
}

// is it a operator?
int	handle_operator(char *line, int *i, t_token **head)
{
	if (line[*i] == '|')
		return ((*i += 1), append_op(head, TOK_PIPE, "|"));
	if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i += 2), append_op(head, TOK_HEREDOC, "<<"));
	if (line[*i] == '<')
		return ((*i += 1), append_op(head, TOK_REDIR_IN, "<"));
	if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i += 2), append_op(head, TOK_REDIR_APP, ">>"));
	if (line[*i] == '>')
		return ((*i += 1), append_op(head, TOK_REDIR_OUT, ">"));
	return (0);
}
