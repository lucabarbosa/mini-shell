/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:19:54 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/04 16:09:16 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

t_token	*lexer(char *input, t_gc **collector)
{
	int		i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|')
			i += handle_pipe(&tokens, collector);
		else if (input[i] == '>')
			i += handle_append_or_out(&tokens, input, i, collector);
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
	expandable_tokens(tokens);
	return (tokens);
}

void	add_token(t_token **token, t_token_type type, char *value, t_gc **coll)
{
	t_token	*new_token;
	t_token	*current;

	new_token = gc_malloc(coll, sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = type;
	new_token->expandable = 0;
	if (value)
		new_token->value = ft_strdup(value, coll);
	else
		new_token->value = NULL;
	new_token->next = NULL;
	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	current = *token;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
}

void	expandable_tokens(t_token *tokens)
{
	t_token	*cr;
	int		i;
	
	
	cr = tokens;
	while (cr)
	{
		if (cr->type == TOKEN_DQUOTE || cr->type == TOKEN_WORD)
		{
			i = 0;
			while (cr->value[i])
			{
				if (cr->value[i] == '$')
					cr->expandable = 1;
				i++;
			}
		}
		cr = cr->next;
	}
}
