/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:13:33 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/19 17:05:29 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	build_arg_from_words(t_shell *sh, const t_cmd *cmd)
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
	else if (cmd->builtin_id == BI_EXIT)
		rc = builtin_exit(sh, argv);
	else if (cmd->builtin_id == BI_EXPORT)
		rc = builtin_export(sh, argv);
	else if (cmd->builtin_id == BI_UNSET)
		rc = builtin_unset(sh, argv);
	else if (cmd->builtin_id == BI_EXIT)
		rc = builtin_exit(sh, argv);
	return (free_argv(argv), rc);
}
