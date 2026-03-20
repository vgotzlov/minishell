/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:13:33 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/17 12:04:45 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_arg_from_words(t_shell *sh, const t_cmd *cmd)
{
	char	**argv;
	int		i;

	argv = (char **)malloc((sizeof(char *) * (size_t)cmd->argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < cmd->argc)
	{
		argv[i] = word_to_string(sh, cmd->argv_words[i]);
		if (!argv[i])
			return (free_argv(argv), NULL);
		i++;
	}
	argv[cmd->argc] = NULL;
	return (argv);
}

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
	argv = build_arg_from_words(sh, cmd);
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
	return (free_argv(argv), rc);
}
