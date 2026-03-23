/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:50:18 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/23 11:26:26 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// convert return value from wait() to "shell" return value
// how process ends?
int	wait_status_to_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

// run the builtin command in parent process
// redirects stdin/stdout according to redirections
// and returns everything to its original state after 
static int	exec_parent_builtin(t_shell *sh, t_cmd *cmd)
{
	int		saved_in;
	int		saved_out;
	int		rc;

	saved_in = -1;
	saved_out = -1;
	if (apply_redirs(cmd, &saved_in, &saved_out, sh) != 0)
	{
		restore_redirs(saved_in, saved_out);
		sh->last_status = 1;
		return (1);
	}
	rc = exec_builtin(sh, cmd);
	restore_redirs(saved_in, saved_out);
	return (rc);
}

// create child, in child run the command, parent -> wait
static int	exec_single_command(t_shell *sh, t_pipeline *p)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), sh->last_status = 1, 1);
	if (pid == 0)
	{
		exec_command_child(sh, p, 0);
		_exit(sh->last_status);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), sh->last_status = 1, 1);
	sh->last_status = wait_status_to_code(status);
	return (sh->last_status);
}

// do a single command or commands with pipe
int	execute_pipeline(t_shell *sh, t_pipeline *p)
{
	int	status;

	if (!sh || !p || p->count <= 0)
		return (1);
	if (prepare_heredocs(sh, p) != 0)
		return (sh->last_status = 1, 1);
	setup_parent_signals();
	if (p->count == 1 && is_stateful_builtin(p->cmds[0]))
		status = exec_parent_builtin(sh, p->cmds[0]);
	else if (p->count == 1)
		status = exec_single_command(sh, p);
	else
		status = exec_multi_pipeline(sh, p);
	setup_interactive_signals();
	return (status);
}
