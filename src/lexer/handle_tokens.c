/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:58:01 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/22 19:36:14 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pipe(t_token **tokens, t_gc **collector)
{
	add_token(tokens, TOKEN_PIPE, "|", collector);
	return (1);
}

int	handle_append_or_out(t_token **tokens, char *str, int i, t_gc **colle)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			add_token(tokens, TOKEN_REDIR_APPEND, ">>", colle);
			return (2);
		}
		else
		{
			add_token(tokens, TOKEN_REDIR_OUT, ">", colle);
			return (1);
		}
	}
	return (-1);
}

int	handle_heredoc_or_in(t_token **tokens, char *str, int i, t_gc **colle)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			add_token(tokens, TOKEN_HEREDOC, "<<", colle);
			return (2);
		}
		else
		{
			add_token(tokens, TOKEN_REDIR_IN, "<", colle);
			return (1);
		}
	}
	return (-1);
}
