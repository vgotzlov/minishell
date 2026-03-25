/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:50:47 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/25 17:02:57 by msnizek          ###   ########.fr       */
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

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == TOK_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	while (tmp)
	{
		if (tmp->type == TOK_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOK_PIPE)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
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
