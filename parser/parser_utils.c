/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:50:47 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/20 15:12:02 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	if (!tokens)
		return (0);
	count = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOK_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv_words = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->builtin_id = -1;
	return (cmd);
}

void	identify_builtins(t_pipeline *p)
{
	int		i;
	t_cmd	*cmd;
	char	*name;

	i = 0;
	while (i < p->count)
	{
		cmd = p->cmds[i];
		// Predpokladáme, že BI_NONE je 0 (alebo si to nastav na svoju hodnotu)
		cmd->builtin_id = 0; 
		if (cmd->argc > 0 && cmd->argv_words && cmd->argv_words[0]->segs)
		{
			name = cmd->argv_words[0]->segs->text;
			if (ft_strncmp(name, "cd", 3) == 0)
				cmd->builtin_id = BI_CD;
			else if (ft_strncmp(name, "pwd", 4) == 0)
				cmd->builtin_id = BI_PWD;
			else if (ft_strncmp(name, "echo", 5) == 0)
				cmd->builtin_id = BI_ECHO;
			else if (ft_strncmp(name, "export", 7) == 0)
				cmd->builtin_id = BI_EXPORT;
			else if (ft_strncmp(name, "unset", 6) == 0)
				cmd->builtin_id = BI_UNSET;
			else if (ft_strncmp(name, "env", 4) == 0)
				cmd->builtin_id = BI_ENV;
			else if (ft_strncmp(name, "exit", 5) == 0)
				cmd->builtin_id = BI_EXIT;
		}
		i++;
	}
}