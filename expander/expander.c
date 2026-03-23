/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:25:45 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/23 12:07:16 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Převede jeden segment na string (vždy alokuje novou paměť).
char	*get_segment_str(t_segment *seg, t_shell *shell)
{
	char	*val;

	if (seg->type == SEG_LIT)
		return (ft_strdup(seg->text));
	if (seg->type == SEG_STATUS)
		return (ft_itoa(shell->last_status));
	if (seg->type == SEG_VAR)
	{
		val = get_env_value(shell->env, seg->text);
		if (val)
			return (ft_strdup(val));
		return (ft_strdup(""));
	}
	return (ft_strdup(""));
}

//projde segmenty, expanduje a spoji
char	*expand_word(t_word *word, t_shell *shell)
{
	t_segment	*tmp;
	char		*result;
	char		*seg_str;

	result = ft_strdup("");
	if (!word || !word->segs)
		return (result);

	tmp = word->segs;
	while (tmp)
	{
		seg_str = get_segment_str(tmp, shell);
		result = join_and_free(result, seg_str);
		tmp = tmp->next;
	}
	return (result);
}
