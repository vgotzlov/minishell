/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:35:26 by msnizek           #+#    #+#             */
/*   Updated: 2026/04/08 23:47:56 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bubble sort
static void	sort_env_array(t_env **arr, int size)
{
	int		i;
	int		j;
	size_t	len;
	t_env	*tmp;

	i = -1;
	while (++i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			len = ft_strlen(arr[j]->key);
			if (ft_strlen(arr[j + 1]->key) > len)
				len = ft_strlen(arr[j + 1]->key);
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, len + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
	}
}

static void	print_array(t_env **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x", 1);
		ft_putstr_fd(arr[i]->key, 1);
		if (arr[i]->val)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(arr[i]->val, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

static int	print_exported_env(t_env *env)
{
	t_env	**arr;
	t_env	*curr;
	int		size;
	int		i;

	curr = env;
	size = 0;
	while (curr && ++size)
		curr = curr->next;
	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return (1);
	curr = env;
	i = 0;
	while (i < size)
	{
		arr[i++] = curr;
		curr = curr->next;
	}
	sort_env_array(arr, size);
	print_array(arr, size);
	free(arr);
	return (0);
}

// separate key and value
static void	process_export_arg(t_shell *sh, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = eq + 1;
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_identifier(key))
		handle_export_error(key, &sh->last_status);
	else
		update_or_add_env(sh, key, value);
	free(key);
}

int	builtin_export(t_shell *sh, char **argv)
{
	int		i;

	if (!argv || !argv[1])
		return (print_exported_env(sh->env));
	sh->last_status = 0;
	i = 1;
	while (argv[i])
	{
		process_export_arg(sh, argv[i]);
		i++;
	}
	return (sh->last_status);
}
