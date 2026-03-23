/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:28:06 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/16 17:28:06 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_apply_redirs(t_cmd *cmd, t_shell *sh)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			fd = r->heredoc_fd;
		else
			fd = open_redir(r, sh);
		if (fd == -1)
			return (1);
		if (dup2(fd, get_target(r->type)) == -1)
		{
			if (fd > 2)
				close(fd);
			return (1);
		}
		if (fd > 2)
			close(fd);
		r = r->next;
	}
	return (0);
}

static int	child_run_builtin(t_shell *sh, t_pipeline *p, t_cmd *cmd)
{
	int	status;

	if (child_apply_redirs(cmd, sh) != 0)
	{
		perror("redirections");
		free_pipeline(p);
		free_shell(sh);
		_exit(1);
	}
	status = exec_builtin(sh, cmd);
	free_pipeline(p);
	free_shell(sh);
	_exit(status);
}

static int	child_run_external(t_shell *sh, t_pipeline *p, t_cmd *cmd)
{
	char		*path;
	char		**argv;

	if (child_apply_redirs(cmd, sh) != 0)
	{
		perror("minishell: redirection");
		free_pipeline(p);
		free_shell(sh);
		_exit(1);
	}
	argv = create_exec_argv(cmd, sh);
	if (!argv || !argv[0])
	{
		if (argv)
			free_str_array(argv);
		free_pipeline(p);
		free_shell(sh);
		_exit(0);
	}
	path = get_child_path(sh, p, argv);
	exec_and_free(sh, p, path, argv);
	return (1);
}

void	exec_command_child(t_shell *sh, t_pipeline *p, int cmd_idx)
{
	t_cmd	*cmd;

	cmd = p->cmds[cmd_idx];
	if (!sh || !cmd)
	{
		free_pipeline(p);
		free_shell(sh);
		_exit(1);
	}
	if (child_setup_signals() != 0)
	{
		free_pipeline(p);
		free_shell(sh);
		_exit(1);
	}
	if (cmd->builtin_id != BI_NONE)
		child_run_builtin(sh, p, cmd);
	else
		child_run_external(sh, p, cmd);
	_exit(sh->last_status);
}
