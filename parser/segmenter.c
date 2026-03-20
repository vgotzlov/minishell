/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segmenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:34:41 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 10:49:26 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Rozseká lexeme na segmenty a provede automatické odstranění vnějších uvozovek
t_segment	*segmentize(char *lexeme)
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
}
