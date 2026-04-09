/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:21:35 by msnizek           #+#    #+#             */
/*   Updated: 2026/04/08 23:47:53 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_shell *sh, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = sh->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				sh->env = curr->next;
			free(curr->key);
			free(curr->val);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_shell *sh, char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			status = 1;
		}
		else
			remove_env_node(sh, argv[i]);
		i++;
	}
	sh->last_status = status;
	return (status);
}
