/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:38:55 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/14 11:38:55 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	init_shell(t_shell *sh, char **envp)
{
	ft_memset(sh, 0, sizeof(t_shell));
	sh->env = init_env_list(envp);
	sh->last_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	t_pipeline	*pipeline;
	char		*line;
	t_token		*tokens;

	(void)argc;
	(void)argv;
	init_shell(&sh, envp);
	while (1)
	{
		setup_interactive_signals();
		g_sig = 0;
		line = readline("minishell$ ");
		if (g_sig == SIGINT)
		{
			sh.last_status = 130;
			g_sig = 0;
			if (line)
				free(line);
			continue ;
		}
		if (!line)
		{
			if (sh.interactive)
				ft_putendl_fd("exit", 1);
			break;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = lexer(line);			
		if (tokens)
		{
			pipeline = parser(tokens);
			if (pipeline)
			{
				execute_pipeline(&sh, pipeline);
				free_pipeline(pipeline);
			}
			else
				sh.last_status = 2;
			free_tokens(tokens);
		}
		free(line);
	}
	free_shell(&sh);
	rl_clear_history();
	return (sh.last_status);
}
