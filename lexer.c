/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:11:36 by vgotzlov          #+#    #+#             */
/*   Updated: 2026/03/06 14:02:19 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;
	int		w_len;
	char	*w_str;
	t_quote	q;

	head = NULL;
	i = 0;
	while (line && line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (handle_operator(line, &i, &head))
			continue ;
		w_len = get_word_length(line, i, &q);
		if (w_len == -1)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
			free_tokens(head);
			return (NULL);
		}
		w_str = ft_substr(line, i, w_len);
		add_token_back(&head, create_token(TOK_WORD, w_str, q));
		i += w_len;
	}
	return (head);
}

// Global variable
extern volatile sig_atomic_t	g_sig;

void	skip_spaces(char *line, int *i);

// lexer_words.c
void	update_quote_state(char c, t_quote *state);
int		is_delimiter(char c);
int		get_word_length(char *line, int start, t_quote *out_quote);

// lexer_operators.c
int		handle_operator(char *line, int *i, t_token **head);

// lexer.c
t_token	*lexer(char *line);

// token_utils.c
t_token	*create_token(t_tok_type type, char *lexeme, t_quote quote_type);
void	add_token_back(t_token **head, t_token *new_token);
void	free_tokens(t_token *head);

// lexer_segments.c
t_segment	*segmentize(char *lexeme);
