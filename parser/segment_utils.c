/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:32:03 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 10:48:48 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*create_segment(t_seg_type type, char *text, t_quote q_ctx)
{
	t_segment	*new;

	new = malloc(sizeof(t_segment));
	if (!new)
		return (NULL);
	new->type = type;
	new->text = text;
	new->quote_ctx = q_ctx;
	new->next = NULL;
	return (new);
}

void	add_segment_back(t_segment **head, t_segment *new_node)
{
	t_segment	*tmp;

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

//Funkce, která zjistí, jestli uvozovka mění náš aktuální stav.
int	is_state_changing_quote(char c, t_quote state)
{
	if (c == '\'' && (state == Q_NONE || state == Q_SINGLE))
		return (1);
	if (c == '"' && (state == Q_NONE || state == Q_DOUBLE))
		return (1);
	return (0);
}
