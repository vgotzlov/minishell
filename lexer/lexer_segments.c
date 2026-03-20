/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:25:29 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 13:14:59 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*create_segment(t_seg_type type, char *text, t_quote q_ctx)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->type = type;
	seg->quote_ctx = q_ctx;
	seg->text = text;
	seg->next = NULL;
	return (seg);
}

void	add_segment_back(t_segment **head, t_segment *new)
{
	t_segment	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// Builds segment list from a raw word string
t_segment	*segmentize(char *lexeme)
{
	t_segment	*head;
	t_quote		state;
	int			i;
	int			start;
	char		*text;

	head = NULL;
	state = Q_NONE;
	i = 0;
	while (lexeme[i])
	{
		start = i;
		if (lexeme[i] == '$' && state != Q_SINGLE)
		{
			i++;
			if (lexeme[i] == '?')
			{
				i++;
				add_segment_back(&head, create_segment(SEG_VAR, text, state));
			}
			else if (ft_isalpha(lexeme[i]) || lexeme[i] == '_')
			{
				start = i;
				while (ft_isalnum(lexeme[i]) || lexeme[i] == '_')
					i++;
				text = ft_substr(lexeme, start, i - start);
				add_segment_back(&head, create_segment(SEG_VAR, text, state));
			}
			else
			{
				text = ft_substr(lexeme, start - 1, i - start + 1);
				add_segment_back(&head, create_segment(SEG_LIT, text, state));
			}
		}
		else if (lexeme[i] == '\'' || lexeme[i] == '"')
		{
			update_quote_state(lexeme[i], &state);
			i++;
		}
		else
		{
			while (lexeme[i] && lexeme[i] != '$'
				&& lexeme[i] != '\'' && lexeme[i] != '"')
				i++;
			text = ft_substr(lexeme, start, i - start);
			add_segment_back(&head, create_segment(SEG_LIT, text, state));
		}
	}
	return (head);
}
