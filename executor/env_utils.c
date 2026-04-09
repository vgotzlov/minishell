/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:37:30 by msnizek           #+#    #+#             */
/*   Updated: 2026/04/08 23:48:01 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_list(char **envp)
{
	t_shell	sh;
	char	*eq;
	char	*key;
	int		i;

	sh.env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key = ft_substr(envp[i], 0, eq - envp[i]);
			update_or_add_env(&sh, key, eq + 1);
			free(key);
		}
		i++;
	}
	return (sh.env);
}

static int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

// linked list to array, because of execve
char	**env_to_array(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (env_list_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (free_array(envp), NULL);
		envp[i] = ft_strjoin(tmp, env->val);
		free(tmp);
		if (!envp[i])
			return (free_array(envp), NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
