/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:19:54 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/14 19:53:51 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

t_token *lexer(char *input, t_gc **collector)
{
    int     i;
    t_token *tokens;
    
    tokens = NULL;
    i = 0;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (input[i] == '|')
            i += handle_pipe(&tokens, collector);
        else if (input[i] == '>')
            i += handle_append_or_out(&tokens,input, i, collector);
        else if (input[i] == '<')
            i += handle_heredoc_or_in(&tokens, input, i, collector);
        else if (input[i] == '\'')
            i += handle_squotes(input + i, &tokens, collector);
        else if (input[i] == '"')
            i += handle_dquotes(input + i, &tokens, collector);
        else
            i += handle_words(input + i, &tokens, collector);
    }
    add_token(&tokens, TOKEN_END, NULL, collector);
    return (tokens);
}

void    add_token(t_token **tokens, t_token_type type, char *value, t_gc **collector)
{
    t_token *new_token;
    t_token *current;

    new_token = gc_malloc(collector, sizeof(t_token));
    if (!new_token)
        return ;
    new_token->type = type;
    if (value)
        new_token->value = ft_strdup(value, collector);
    else
        new_token->value = NULL;
    new_token->next = NULL;
    if (*tokens == NULL)
    {
        *tokens = new_token;
        return ;
    }
    current = *tokens;
    while (current->next != NULL)
        current = current->next;
    current->next = new_token;
}