/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:13:33 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/20 14:53:12 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stateful_builtin(const t_cmd *cmd)
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

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	char	**argv;
	int		rc;

	if (!sh || !cmd || cmd->argc == 0 || cmd->builtin_id == BI_NONE)
		return (0);
	argv = create_exec_argv(cmd, sh);
	if (!argv)
		return (sh->last_status = 1, 1);
	rc = 1;
	if (cmd->builtin_id == BI_ECHO)
		rc = builtin_echo(argv);
	else if (cmd->builtin_id == BI_PWD)
		rc = builtin_pwd(argv);
	else if (cmd->builtin_id == BI_ENV)
		rc = builtin_env(sh, argv);
	else if (cmd->builtin_id == BI_CD)
		rc = builtin_cd(sh, argv);
	else if (cmd->builtin_id == BI_EXPORT)
		rc = builtin_export(sh, argv);
	else if (cmd->builtin_id == BI_UNSET)
		rc = builtin_unset(sh, argv);
	else if (cmd->builtin_id == BI_EXIT)
		rc = builtin_exit(sh, argv);
	free_str_array(argv);
	return (rc);
}
