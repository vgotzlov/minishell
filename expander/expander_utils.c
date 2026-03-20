/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:25:38 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 15:25:41 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//hleda env v t_env
char	*get_env_value(t_env *env_list, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, key_len + 1) == 0)
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	**create_exec_argv(t_cmd *cmd, t_shell *shell)
{
	char	**argv;
	int		i;

	if (!cmd || cmd->argc == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < cmd->argc)
	{
		argv[i] = expand_word(cmd->argv_words[i], shell);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


