/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:14 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/11 14:31:14 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_target(int type)
{
	if (type == R_IN || type == R_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

char	*word_to_pure_string(t_word *w)
{
	t_segment	*seg;
	char		*res;
	char		*tmp;

	if (!w || !w->segs)
		return (ft_strdup(""));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	seg = w->segs;
	while (seg)
	{
		if (seg->text)
		{
			tmp = res;
			res = ft_strjoin(tmp, seg->text);
			free(tmp);
			if (!res)
				return (NULL);
		}
		seg = seg->next;
	}
	return (res);
}

int	apply_redirs(t_cmd *cmd, int *saved_in, int *saved_out)
{
	t_redir	*r;
	int		fd;
	int		target;

	r = cmd->redirs;
	while (r)
	{
		target = get_target(r->type);
		if (save_original_fd(target, saved_in, saved_out) != 0)
			return (1);
		fd = open_redir(&cmd->redirs);
		if (fd == -1)
		{
			if (r->type == R_HEREDOC)
				return (perror("heredoc"), 1);
			else
				return (perror("open"), 1);
		}
		if (dup2(fd, target) == -1)
			return (close(fd), perror("dup2"), 1);
		r = r->next;
	}
	close(fd);
	return (0);
}

void	restore_redirs(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}
