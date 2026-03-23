/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:25:38 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/23 12:15:15 by msnizek          ###   ########.fr       */
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

char    **create_exec_argv(t_cmd *cmd, t_shell *shell)
{
    char        **argv;
    char        *expanded;
    int         i;
    int         j;
    t_segment   *seg;
    int         only_var;

	if (!cmd || cmd->argc == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	j = 0;
	while (i < cmd->argc)
	{
		expanded = expand_word(cmd->argv_words[i], shell);
		only_var = 1;
		if (cmd->argv_words[i] && cmd->argv_words[i]->segs)
		{
			seg = cmd->argv_words[i]->segs;
			while (seg)
			{
				if (seg->type != SEG_VAR)
					only_var = 0;
				seg = seg->next;
			}
		}
		else
			only_var = 0;
		if (expanded && expanded[0] == '\0' && only_var)
			free(expanded);
		else
			argv[j++] = expanded;
		i++;
	}
	argv[j] = NULL;
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


