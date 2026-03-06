/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:50:18 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/19 17:11:09 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// convert return value from wait() to "shell" return value
// how process ends?
int	wait_status_to_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFESIGNALED(status))
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

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in < 0 || saved_out < 0)
		return (perror("dup"), sh->last_status = 1, 1);
	if (apply_redirs(cmd, &saved_in, &saved_out) != 0)
		return (restore_redirs(saved_in, saved_out), sh->last_status = 1, 1);
	rc = exec_builtin(sh, cmd);
	restore_redirs(saved_in, saved_out);
	return (rc);
}

// create child, in child run the command, parent -> wait
static int	exec_single_command(t_shell *sh, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), sh->last_status = 1, 1);
	if (pid == 0)
	{
		exec_command_child(sh, cmd);
		_exit(sh->last_status);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), sh->last_status = 1, 1);
	sh->last_status = wait_status_to_code(status);
	return (sh->last_status);
}

static int	is_stateful_builtin(const t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->builtin_id == BI_CD)
		return (1);
	if (cmd->builtin_id == BI_EXPORT)
		return (1);
	if (cmd->builtin_id == BI_UNSET)
		return (1);
	if (cmd->builtin_id == BI_EXIT)
		return (1);
	return (0);
}

// do a single command or commands with pipe
int	execute_pipeline(t_shell *sh, t_pipeline *p)
{
	if (!sh || !p || p->count <= 0)
		return (perror("execute_pipeline"), 1);
	if (prepare_heredocs(sh, p) != 0)
		return (sh->last_status = 1, 1);
	if (p->count == 1 && is_stateful_builtin(p->cmds[0]))
		return (exec_parent_builtin(sh, p->cmds[0]));
	if (p->count == 1)
		return (exec_single_command(sh, p->cmds[0]));
	return (exec_multi_pipeline(sh, p));
}
