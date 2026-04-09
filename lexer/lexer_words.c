/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:10:40 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/04/08 23:47:46 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in which quotes are you
void	update_quote_state(char c, t_quote *state)
{
	if (c == '\'' && *state == Q_NONE)
		*state = Q_SINGLE;
	else if (c == '\'' && *state == Q_SINGLE)
		*state = Q_NONE;
	else if (c == '"' && *state == Q_NONE)
		*state = Q_DOUBLE;
	else if (c == '"' && *state == Q_DOUBLE)
		*state = Q_NONE;
}

int	is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

// delka slova, vraci -1, pokud nejsou zavorky uzavreny
int	get_word_length(char *line, int start, t_quote *out_quote)
{
	int		len;
	t_quote	state;
	t_quote	dominant;

	len = 0;
	state = Q_NONE;
	dominant = Q_NONE;
	while (line[start + len])
	{
		update_quote_state(line[start + len], &state);
		if (state != Q_NONE)
			dominant = state;
		if (state == Q_NONE && is_delimiter(line[start + len]))
			break ;
		len++;
	}
	if (state != Q_NONE)
		return (-1);
	*out_quote = dominant;
	return (len);
}
