/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:52 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/05 20:25:14 by iaratang         ###   ########.fr       */
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

typedef struct s_mshell	t_mshell;

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
	int				expandable;
}	t_token;

t_token	*lexer(char *input, t_gc **collector);

int		handle_pipe(t_token **tokens, t_gc **collector);
int		handle_words(char *str, t_token **tokens, t_gc **collector);
int		handle_squotes(char *str, t_token **tokens, t_gc **collector);
int		handle_dquotes(char *str, t_token **tokens, t_gc **collector);
int		is_metachar(char c);

void	add_token(t_token **token, t_token_type type, char *value, t_gc **coll);

int		handle_append_or_out(t_token **tokens, char *str, int i, t_gc **colle);
int		handle_heredoc_or_in(t_token **tokens, char *str, int i, t_gc **colle);

void	expandable_tokens(t_token *tokens);

void	expand(t_token *tokens, t_gc **gc, t_mshell *shell);

#endif
