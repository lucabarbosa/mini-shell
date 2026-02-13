/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:52 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 15:50:22 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_mshell		t_mshell;
typedef struct s_envlist	t_envlist;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
	int				expandable;
}	t_token;

typedef struct s_expctx
{
	char		*arg;
	char		*res;
	t_gc		**gc;
	t_mshell	*shell;
}	t_expctx;

t_token	*lexer(char *input, t_gc **collector);

int		handle_pipe(t_token **tokens, t_gc **collector);

void	add_token(t_token **token, t_token_type type, char *value, t_gc **coll);

int		handle_append_or_out(t_token **tokens, char *str, int i, t_gc **colle);
int		handle_heredoc_or_in(t_token **tokens, char *str, int i, t_gc **colle);

void	expandable_tokens(t_token *tokens);

char	*srchcmd(char *cmd, t_envlist *env);
int		envchr(char c);

void	expand(t_token *tokens, t_gc **gc, t_mshell *shell);
int		cond(char *arg, int i);
void	handle_pid(t_expctx *ctx, int *i);
void	handle_status(t_expctx *ctx, int *i);
void	handle_env(t_expctx *ctx, int *i);

int		handle_concat_token(char *str, t_token **tokens, t_gc **gc);
int		process_squote(char *str, char **result, t_gc **gc);
int		process_dquote(char *str, char **result, int *expandable, t_gc **gc);
int		process_word_part(char *str, char **result, int *expandable, t_gc **gc);
int		ft_is_metachar(char c);
int		is_operator(char c);
int		is_word_start(char c);

void    print_tokens(t_token *tokens);

#endif
