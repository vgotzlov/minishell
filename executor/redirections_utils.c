/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:49:47 by msnizek           #+#    #+#             */
/*   Updated: 2026/04/08 23:47:23 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// duplicates fd
int	save_original_fd(int target, int *saved_in, int *saved_out)
{
	if (target == STDIN_FILENO)
	{
		if (saved_in && *saved_in == -1)
		{
			*saved_in = dup(STDIN_FILENO);
			if (*saved_in == -1)
				return (perror("dup"), 1);
		}
		return (0);
	}
	if (saved_out && *saved_out == -1)
	{
		*saved_out = dup(STDOUT_FILENO);
		if (*saved_out == -1)
			return (perror("dup"), 1);
	}
	return (0);
}

int	open_redir(t_redir *r, t_shell *sh)
{
	char	*path;
	int		fd;

	path = expand_word(r->target, sh);
	if (!path || path[0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		if (path)
			free(path);
		return (-1);
	}
	fd = -1;
	if (r->type == R_IN)
		fd = open(path, O_RDONLY);
	else if (r->type == R_OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == R_APP)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
	}
	free(path);
	return (fd);
}
