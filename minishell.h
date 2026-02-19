/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:26:32 by msnizek           #+#    #+#             */
/*   Updated: 2026/02/19 17:03:04 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include "libft.h"

// Tokens
typedef enum e_tok_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APP,
	TOK_HEREDOC
}	t_tok_type;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef enum e_builtin
{
	BI_NONE = 0,
	BI_ECHO,
	BI_PWD,
	BI_ENV,
	BI_CD,
	BI_EXPORT,
	BI_UNSET,
	BI_EXIT
}	t_builtin;

typedef struct s_token
{
	t_tok_type		type;
	char			*lexeme;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

// Word segments
typedef enum e_seg_type
{
	SEG_LIT,
	SEG_VAR,
	SEG_STATUS
}	t_seg_type;

typedef struct s_segment
{
	t_seg_type			type;
	t_quote				quote_ctx;
	char				*text;
	struct s_segment	*next;
}	t_segment;

typedef struct s_word
{
	t_segment	*segs;
}	t_word;

// Redirections and Heredoc
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APP,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	t_word			*target;
	char			*delim_raw;
	int				delim_quoted;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

// Command and Pipeline
typedef struct s_cmd
{
	t_word	**argv_words;
	int		argc;
	t_redir	*redirs;
	int		builtin_id;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	**cmds;
	int		count;
	pid_t	*pids;
}	t_pipeline;

// Environment and expansion
typedef struct s_env
{
	char			*key;
	char			*val;
	int				exported;
	struct s_env	*next;
}	t_env;

// Execution context
typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		interactive;
	int		save_stdin;
	int		save_stdout;
}	t_shell;

// Global variable
extern volatile sig_atomic_t	g_sig;

// Builtins
int			append_str(char **out, const char *s);
int			append_lit(t_segment *seg, char **out);
int			append_var(t_shell *sh, t_segment *seg, char **out);
int			append_status(t_shell *sh, char **out);
char		word_to_string(t_shell *sh, t_word *w);
char		build_arg_from_words(t_shell *sh, const t_cmd *cmd);
int			exec_builtin(t_shell *sh, t_cmd *cmd);

// Child
void		exec_command_child(t_shell *sh, t_cmd *cmd);

// Environment
const char	env_get(const t_env *env, const char *key);

// Pipeline
int			exec_multi_pipeline(t_shell *sh, t_pipeline *p);
int			wait_status_to_code(int status);
int			execute_pipeline(t_shell *sh, t_pipeline *p);

// Heredocs
int			prepare_heredocs(t_shell *sh, t_pipeline *p);

// Path
char		*get_cmd_path(t_shell *sh, char *cmd);

// Redirections
int			save_original_fd(int target, int *saved_in, int *saved_out);
int			open_redir(t_redir *r);
int			get_target(int type);
char		*word_to_pure_string(t_word *w);
int			apply_redirs(t_cmd *cmd, int *saved_in, int *saved_out);
void		restore_redirs(int saved_in, int saved_out);

#endif