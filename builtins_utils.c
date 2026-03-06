/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:41:55 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/19 17:09:52 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_str(char **out, const char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = *out;
	*out = ft_strjoin(tmp, s);
	free(tmp);
	if (!*out)
		return (1);
	return (0);
}

int	append_lit(t_segment *seg, char **out)
{
	if (!seg || !out)
		return (1);
	if (append_str(&out, seg->text) != 0)
		return (1);
	return (0);
}

int	append_var(t_shell *sh, t_segment *seg, char **out)
{
	const char	*val;

	if (!sh || !seg || !out)
		return (1);
	val = env_get(sh->env, seg->text);
	if (append_str(out, val) != 0)
		return (1);
	return (0);
}

int	append_status(t_shell *sh, char **out)
{
	char	*tmp;

	if (!sh || !out)
		return (1);
	tmp = ft_itoa(sh->last_status);
	if (!tmp)
		return (1);
	if (append_str(out, tmp) != 0)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

char	word_to_string(t_shell *sh, t_word *w)
{
	t_segment	*seg;
	char		*out;
	int			err;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	if (!w)
		return (out);
	seg = w->segs;
	while (seg)
	{
		err = 0;
		if (seg->type == SEG_LIT)
			err = append_lit(seg, &out);
		else if (seg->type == SEG_VAR)
			err = append_var(sh, seg, &out);
		else if (seg->type == SEG_STATUS)
			err = append_status(sh, &out);
		if (err)
			return (free(out), NULL);
		seg = seg->next;
	}
	return (out);
}
