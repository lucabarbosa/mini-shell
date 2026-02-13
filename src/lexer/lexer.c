/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:19:54 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 16:10:12 by iaratang         ###   ########.fr       */
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
		if (input[i] == '\0')
			add_token(&tokens, TOKEN_END, NULL, collector);
		if (input[i] == '|')
			i += handle_pipe(&tokens, collector);
		else if (input[i] == '>')
			i += handle_append_or_out(&tokens, input, i, collector);
		else if (input[i] == '<')
			i += handle_heredoc_or_in(&tokens, input, i, collector);
		else if (input[i] == '\'' || input[i] == '"' || is_word_start(input[i]))
			i += handle_concat_token(input + i, &tokens, collector);
		else
			i++;
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
	new_token->prev = NULL;
	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	current = *token;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	expandable_tokens(t_token *tokens)
{
	t_token	*cr;
	int		i;

	if (!tokens)
		return ;
	cr = tokens;
	while (cr)
	{
		if (cr->type == TOKEN_DQUOTE || cr->type == TOKEN_WORD)
		{
			i = 0;
			while (cr->value[i])
			{
				if (cr->value[i] == '$' && (cr->prev && cr->prev->type != TOKEN_HEREDOC))
					cr->expandable = 1;
				i++;
			}
		}
		cr = cr->next;
	}
}

void    print_tokens(t_token *tokens)
{
    t_token *current;
    const char  *type_names[] = {
        "WORD", "PIPE", "REDIR_IN",
        "REDIR_OUT", "REDIR_APPEND",
        "HEREDOC", "ENV_VAR", "SQUOTE",
        "DQUOTE", "END"};
        
    current = tokens;
    printf("==========TOKENS==========\n");
    while (current)
    {
        printf("Type: %-15s\n", type_names[current->type]);
        printf("Value: %s\n", current->value);
        printf("============\n");
        current = current->next;
    }
    
    
}