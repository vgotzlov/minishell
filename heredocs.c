/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:06:53 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/11 17:06:53 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hd_read_loop(t_redir *r, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("$> ");
		if (!line)
			break ;
		if (ft_strcmp(line, r->delim_raw) == 0)
			return (free(line), 0);
		if (write(fd, line, ft_strlen(line) == -1 || write(fd, "\n", 1) == -1))
			return (free(line), 1);
		free(line);
	}
	return (0);
}

static int	handle_single_heredoc(t_shell *sh, t_redir *r)
{
	int		fd[2];

	(void)sh;
	if (pipe(fd) == -1)
		return (perror("heredoc pipe"), 1);
	if (hd_read_loop(r, fd[1]) != 0)
		return (close(fd[0]), close(fd[1]), 1);
	close(fd[1]);
	if (r->heredoc_fd != -1)
		close(r->heredoc_fd);
	r->heredoc_fd = fd[0];
	return (0);
}

int	prepare_heredocs(t_shell *sh, t_pipeline *p)
{
	t_redir	*r;
	int		i;

	if (!sh || !p)
		return (1);
	i = 0;
	while (i < p->count)
	{
		r = p->cmds[i]->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				if (handle_single_heredoc(sh, r) != 0)
					return (1);
			}
			r = r->next;
		}
		i++;
	}
	return (0);
}
