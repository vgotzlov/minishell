/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:19:38 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/25 16:09:36 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*init_pipeline(int cmd_count)
{
	t_pipeline	*pipe;
	int			i;

	pipe = ft_calloc(1, sizeof(t_pipeline));
	if (!pipe)
		return (NULL);
	pipe->count = cmd_count;
	pipe->cmds = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
	pipe->pids = NULL;
	if (!pipe->cmds)
	{
		free(pipe);
		return (NULL);
	}
	i = 0;
	while (i <= cmd_count)
		pipe->cmds[i++] = NULL;
	return (pipe);
}

t_pipeline	*parser(t_token *tokens)
{
	t_pipeline	*pipeline;
	int			cmd_count;

	if (!tokens)
		return (NULL);
	if (!check_syntax(tokens))
		return (NULL);
	cmd_count = count_commands(tokens);
	pipeline = init_pipeline(cmd_count);
	if (!pipeline)
		return (NULL);
	fill_pipeline(pipeline, tokens);
	identify_builtins(pipeline);
	return (pipeline);
}
