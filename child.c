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

static int	child_setup_signals()
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (perror("SIGINT"), 1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (perror("SIGQUIT"), 1);
	return (0);
}

static int	child_apply_redirs(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			fd = r->heredoc_fd;
		else
			fd = open_redir(r);
		if (fd == -1)
			return (perror("redirection"), 1);
		if (dup2(fd, get_target(r->type)) == -1)
			return (perror("dup2"), 1);
		if (fd > 2)
			close(fd);
		r = r->next;
	}
	return (0);
}

static int	child_run_builtin(t_shell *sh, t_cmd *cmd)
{
	int	status;

	if (child_apply_redirs(cmd) != 0)
		_exit(1);
	status = exec_builtin(sh, cmd);
	_exit(status);
}

static int	child_run_external(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;

	if (child_apply_redirs(cmd) != 0)
		_exit(1);
	argv = build_arg_from_words(sh, cmd);
	if (!argv || !argv[0])
		_exit(0);
	path = get_cmd_path(sh, argv[0]);
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		_exit(127);
	}
	envp = env_to_array(sh->env);
	execve(path, argv, envp);
	perror("execve");
	_exit(126);
}

void	exec_command_child(t_shell *sh, t_cmd *cmd)
{
	if (!sh || !cmd)
		return (perror("exec_command_child"), 1);
	if (child_setup_signals() != 0)
		_exit(1);
	if (cmd->builtin_id != BI_NONE)
		child_run_builtin(sh, cmd);
	else
		child_run_external(sh, cmd);
	_exit(sh->last_status);
}
