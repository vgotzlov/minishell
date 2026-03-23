/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:39:30 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/19 14:11:47 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_export_error(char *id, int *last_status)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putendl_fd(" : not a valid identifier", 2);
	*last_status = 1;
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->val = ft_strdup(value);
	else
		new_node->val = NULL;
	new_node->exported = 1;
	new_node->next = NULL;
	return (new_node);
}

void	update_or_add_env(t_shell *sh, char *key, char *value)
{
	t_env	*curr;

	curr = sh->env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value)
			{
				free(curr->val);
				curr->val = ft_strdup(value);
			}
			curr->exported = 1;
			return ;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (!sh->env)
		sh->env = new_env_node(key, value);
	else
		curr->next = new_env_node(key, value);
}
