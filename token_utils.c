/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:38:14 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 14:06:03 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_tok_type type, char *lexeme, t_quote quote_type)
{
	t_token	*new;

	*new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->lexeme = lexeme;
	new->quote = quote_type;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->lexeme)
			free(head->lexeme);
		free(head);
		head = tmp;
	}
}
