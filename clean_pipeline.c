/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:20:55 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/17 19:20:55 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_segments(t_segment *seg)
{
	t_segment	*tmp;

	while (seg)
	{
		tmp = seg;
		seg = seg->next;
		if (tmp->text)
			free(tmp->text);
		free(tmp);
	}
}

static void	free_words(t_word *word)
{
	if (!word)
		return ;
	if (word->segs)
		free_segments(word->segs);
	free(word);
}

static void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->heredoc_fd != -1)
			close(tmp->heredoc_fd);
		if (tmp->target)
			free_words(tmp->target);
		free(tmp);
	}
}

void	free_pipeline(t_pipeline *p)
{
	int	i;
	int	j;

	if (!p)
		return ;
	i = 0;
	while (i < p->count)
	{
		if (p->cmds[i])
		{
			j = 0;
			while (j < p->cmds[i]->argc)
				free_words(p->cmds[i]->argv_words[j++]);
			free(p->cmds[i]->argv_words);
			free_redirections(p->cmds[i]->redirs);
			free(p->cmds[i]);
		}
		i++;
	}
	free(p->cmds);
	if (p->pids)
		free(p->pids);
	free(p);
}
