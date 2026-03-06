/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:50:47 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 15:19:23 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	if (!tokens)
		return(0);
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

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv_words = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->builtin_id = -1;
	return(cmd);
}