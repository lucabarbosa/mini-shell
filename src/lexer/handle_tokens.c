/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:58:01 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/14 19:19:41 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_pipe(t_token **tokens, t_gc **collector)
{
    add_token(tokens, TOKEN_PIPE, "|", collector);
    return (1);
}

int handle_append_or_out(t_token **tokens, char *str, int i, t_gc **collector)
{
    if (str[i] == '>')
    {
        if (str[i + 1] == '>')
        {
            add_token(tokens, TOKEN_REDIR_APPEND, ">>", collector);
            return (2);
        }
        else
        {
            add_token(tokens, TOKEN_REDIR_OUT, ">", collector);
            return (1);    
        }
    }
    return (-1);
}

int handle_heredoc_or_in(t_token **tokens, char *str, int i, t_gc **collector)
{
    if (str[i] == '<')
    {
        if (str[i + 1] == '<')
        {
            add_token(tokens, TOKEN_HEREDOC, ">>", collector);
            return (2);
        }
        else
        {
            add_token(tokens, TOKEN_REDIR_IN, "<", collector);
            return (1);
        }
    }
    return (-1);
}
