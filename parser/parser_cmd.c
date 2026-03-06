/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:53:18 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 18:05:58 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd(t_cmd *cmd, t_token **tokens)
{
	int		i;
	t_token	*tmp;

	tmp = *tokens;
	cmd->argc = count_args(tmp);
	cmd->argv_words = malloc(sizeof(t_word *) * (cmd->argc + 1));
	i = 0;
	while (tmp && tmp->type != TOK_PIPE)
	{
		if (is_redir_token(tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		else if (tmp->type == TOK_WORD)
		{
			cmd->argv_words[i++] = create_word_node(tmp->lexeme);
			tmp = tmp->next;
		}
	}
	cmd->argv_words[i] = NULL;
	if (tmp && tmp->type == TOK_PIPE)
		tmp = tmp->next;
	*tokens = tmp;
}

void	fill_pipeline(t_pipeline *pipe, t_token *tokens)
{
	int		i;
	t_token	*current_token;

	i = 0;
	current_token = tokens;
	while (i < pipe->count && current_token)
	{
		pipe->cmds[i] = init_cmd();
		if (!pipe->cmds[i])
			return ;
		fill_cmd(pipe->cmds[i], &current_token);
		i++;
	}
}