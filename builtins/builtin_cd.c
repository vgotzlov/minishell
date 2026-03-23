/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:30:25 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/14 00:14:08 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_cd_path(t_shell *sh, char **argv)
{
	const char	*path;

	if (!argv[1])
	{
		path = env_get(sh->env, "HOME");
		if (!path || !*path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		return (path);
	}
	return (argv[1]);
}

int	builtin_cd(t_shell *sh, char **argv)
{
	const char	*path;
	char		old_pwd[PATH_MAX];
	char		new_pwd[PATH_MAX];

	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (sh->last_status = 1, 1);
	}
	path = get_cd_path(sh, argv);
	if (!path)
		return (sh->last_status = 1, 1);
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		old_pwd[0] = '\0';
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (sh->last_status = 1, 1);
	}
	update_or_add_env(sh, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, PATH_MAX))
		update_or_add_env(sh, "PWD", new_pwd);
	return (sh->last_status = 0, 0);
}
