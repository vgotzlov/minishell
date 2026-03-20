/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:49:47 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/20 14:26:21 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(path);
	return (fd);
}
