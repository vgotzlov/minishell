/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:50:18 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/06 16:42:46 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_pipe_fds(int prev_fd, int pipe_fds[2], int i, int count)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < count - 1)
		dup2(pipe_fds[1], STDOUT_FILENO);
	if (i < count - 1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
}

static int	move_pipe_fd(int pipe_fds[2], int i, int count)
{
	if (i < count - 1)
		close(pipe_fds[1]);
	if (i < count - 1)
		return (pipe_fds[0]);
	return (-1);
}

static int	wait_for_pipeline(t_shell *sh, t_pipeline *p)
{
	int	i;
	int	status;
	int	last_raw_status;

	i = 0;
	last_raw_status = 0;
	while (i < p->count)
	{
		if (waitpid(p->pids[i], &status, 0) == -1)
			perror("waitpid");
		if (i == p->count - 1)
			last_raw_status = status;
		i++;
	}
	sh->last_status = wait_status_to_code(last_raw_status);
	return (sh->last_status);
}

int	exec_multi_pipeline(t_shell *sh, t_pipeline *p)
{
	int	pipe_fds[2];
	int	prev_fd;
	int	i;

	p->pids = (pid_t *)malloc(sizeof(pid_t) * p->count);
	if (!p->pids)
		return (perror("malloc"), 1);
	prev_fd = -1;
	i = -1;
	while (++i < p->count)
	{
		if (i < p->count - 1 && pipe(pipe_fds) == -1)
			return (perror("pipe"), 1);
		p->pids[i] = fork();
		if (p->pids[i] == -1)
			return (perror("fork"), 1);
		if (p->pids[i] == 0)
		{
			manage_pipe_fds(prev_fd, pipe_fds, i, p->count);
			exec_command_child(sh, p->cmds[i]);
		}
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = move_pipe_fd(pipe_fds, i, p->count);
	}
	return (wait_for_pipeline(sh, p));
}
