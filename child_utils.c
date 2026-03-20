/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:13:20 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/20 11:37:05 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_path(char *path, char **argv, t_shell *sh, t_pipeline *p)
{
	struct stat	path_stat;

	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_argv(argv);
		free_pipeline(p);
		free_shell(sh);
		_exit(127);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		free(path);
		free_argv(argv);
		free_pipeline(p);
		free_shell(sh);
		_exit(126);
	}
}

void	exec_and_free(t_shell *sh, t_pipeline *p, char *path, char **argv)
{
	char		**envp;

	check_path(path, argv, sh, p);
	envp = env_to_array(sh->env);
	if (!envp)
	{
		free(path);
		free_argv(argv);
		free_pipeline(p);
		free_shell(sh);
		_exit(1);
	}
	execve(path, argv, envp);
	perror(argv[0]);
	free(path);
	free_argv(argv);
	free_array(envp);
	free_pipeline(p);
	free_shell(sh);
	_exit(126);
}

char	*get_child_path(t_shell *sh, t_pipeline *p, char **argv)
{
	char		*path;

	path = get_cmd_path(sh, argv[0]);
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_argv(argv);
		free_pipeline(p);
		free_shell(sh);
		_exit(127);
	}
	return (path);
}
