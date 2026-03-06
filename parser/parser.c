/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:19:38 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 17:04:36 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*init_pipeline(int cmd_count)
{
	t_pipeline	*pipe;
	int			i;

	pipe = malloc(sizeof(t_pipeline));
	if (!pipe)
		return (NULL);
	pipe->count = cmd_count;
	pipe->cmds = malloc(sizeof(t_cmd *) * (cmd_count + 1));
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
	cmd_count = count_commands(tokens);
	pipeline = init_pipeline(cmd_count);
	if (!pipeline)
		return (NULL);
	return (pipeline);
}