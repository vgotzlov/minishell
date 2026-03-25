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

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static int	process_heredoc_line(t_redir *r, int fd)
{
	char	*line;

	line = readline("$> ");
	if (g_sig == SIGINT)
		return (1);
	if (!line)
		return (-1);
	if (!r->delim_raw)
	{
		printf("CHYBA PARSERU: r->delim_raw je NULL!\n");
		free(line);
		return (-1);
	}
	if (ft_strncmp(line, r->delim_raw, ft_strlen(r->delim_raw) + 1) == 0)
	{
		free(line);
		return (-1);
	}
	ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

static int	hd_read_loop(t_redir *r, int fd)
{
	int	stdin_copy;
	int	status;

	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
		return (1);
	signal(SIGINT, handle_sigint_heredoc);
	status = 0;
	while (status == 0)
		status = process_heredoc_line(r, fd);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	signal(SIGINT, handle_sigint);
	if (status == 1)
		return (1);
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
	i = -1;
	while (++i < p->count)
	{
		if (!p->cmds[i])
		{
			i++;
			continue ;
		}
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
	}
	return (0);
}
