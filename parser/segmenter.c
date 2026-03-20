/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segmenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:34:41 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 13:23:13 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Rozseká lexeme na segmenty a provede automatické odstranění vnějších uvozovek
/*t_segment	*segmentize(char *lexeme)
{
	t_segment	*head;
	int			i;
	t_quote		state;

	head = NULL;
	i = 0;
	state = Q_NONE;
	while (lexeme[i])
	{
		if (is_state_changing_quote(lexeme[i], state))
		{
			update_quote_state(lexeme[i], &state);
			i++;
		}
		else if (lexeme[i] == '$' && state != Q_SINGLE)
			handle_dollar(lexeme, &i, state, &head);
		else
			handle_literal(lexeme, &i, state, &head);
	}
	return (head);
}*/
