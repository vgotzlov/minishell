/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:37:30 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/19 17:09:02 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	env_get(const t_env *env, const char *key)
{
	while (env)
	{
		if (env->key && key && ft_strcmp(env->key, key) == 0)
		{
			if (env->val)
				return (env->val);
			return ("");
		}
		env = env->next;
	}
	return ("");
}
