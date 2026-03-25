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

static int	check_input(t_shell *sh, char *line)
{
	if (g_sig == SIGINT)
	{
		sh->last_status = 130;
		g_sig = 0;
		if (line)
			free(line);
		return (1);
	}
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("exit", 1);
		return (2);
	}
	if (*line == '\0')
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	process_line(t_shell *sh, char *line)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	add_history(line);
	tokens = lexer(line);
	if (tokens)
	{
		pipeline = parser(tokens);
		if (pipeline)
		{
			execute_pipeline(sh, pipeline);
			free_pipeline(pipeline);
		}
		else
			sh->last_status = 2;
		free_tokens(tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	char		*line;
	int			status;

	(void)argc;
	(void)argv;
	init_shell(&sh, envp);
	while (1)
	{
		setup_interactive_signals();
		g_sig = 0;
		line = readline("minishell$ ");
		status = check_input(&sh, line);
		if (status == 2)
			break ;
		if (status == 1)
			continue ;
		process_line(&sh, line);
		free(line);
	}
	free_shell(&sh);
	rl_clear_history();
	return (sh.last_status);
}
