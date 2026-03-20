/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:22:54 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 10:45:15 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Převede typ tokenu z lexeru na typ redirekce pro parser.
static t_redir_type	get_redir_type(t_tok_type tok_type)
{
	if (tok_type == TOK_REDIR_IN)
		return (R_IN);
	if (tok_type == TOK_REDIR_OUT)
		return (R_OUT);
	if (tok_type == TOK_REDIR_APP)
		return (R_APP);
	return (R_HEREDOC);
}

// Vytvoří a zinicializuje nový node t_redir.
t_redir	*create_redir_node(t_redir_type type, char *target_lexeme)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->target = create_word_node(target_lexeme);
	node->delim_raw = NULL;
	node->delim_quoted = 0;
	node->heredoc_fd = -1;
	node->next = NULL;
	return (node);
}

void	add_redir_back(t_redir **head, t_redir *new_node)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

// token redir a tok dalsi v rade, posune pointer za nasledujici tok
int	handle_redirection(t_cmd *cmd, t_token **current_token)
{
	t_token			*op_tok;
	t_token			*target_tok;
	t_redir_type	r_type;
	t_redir			*new_redir;

	op_tok = *current_token;
	target_tok = op_tok->next;
	if (!target_tok || target_tok->type != TOK_WORD)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (0);
	}
	r_type = get_redir_type(op_tok->type);
	new_redir = create_redir_node(r_type, target_tok->lexeme);
	if (!new_redir)
		return (0);
	add_redir_back(&(cmd->redirs), new_redir);
	*current_token = target_tok->next;
	return (1);
}
