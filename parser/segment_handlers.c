/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:33:23 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 10:46:57 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(char *str, int *i, t_quote state, t_segment **head)
{
	int		start;
	char	*text;

	(*i)++;
	if (str[*i] == '?')
	{
		add_segment_back(head,
			create_segment(SEG_STATUS, ft_strdup("?"), state));
		(*i)++;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		start = *i;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		text = ft_substr(str, start, *i - start);
		add_segment_back(head, create_segment(SEG_VAR, text, state));
	}
	else
	{
		add_segment_back(head, create_segment(SEG_LIT, ft_strdup("$"), state));
	}
}

void	handle_literal(char *str, int *i, t_quote state, t_segment **head)
{
	int		start;
	char	*text;

	start = *i;
	while (str[*i])
	{
		if (is_state_changing_quote(str[*i], state))
			break ;
		if (str[*i] == '$' && state != Q_SINGLE)
			break ;
		(*i)++;
	}
	text = ft_substr(str, start, *i - start);
	add_segment_back(head, create_segment(SEG_LIT, text, state));
}
