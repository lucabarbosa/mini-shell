/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:19:08 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/12 17:38:55 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	handle_words(char *str, t_token **tokens, t_gc **gc)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != ' ' && !is_metachar(str[i]))
		i++;
	word = ft_substr(str, 0, i, gc);
	add_token(tokens, TOKEN_WORD, word, gc);
	return (i);
}

int	handle_squotes(char *str, t_token **tokens, t_gc **gc)
{
	int		i;
	char	*content;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
	{
		content = ft_substr(str, 1, i - 1, gc);
		add_token(tokens, TOKEN_SQUOTE, content, gc);
		return (i + 1);
	}
	else
	{
		add_token(tokens, TOKEN_END, NULL, gc);
		ft_putstr_fd("Syntax Error: Unclosed Quotes", 2);
		return (i);
	}
}

int	handle_dquotes(char *str, t_token **tokens, t_gc **gc)
{
	int		i;
	char	*content;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '"')
	{
		content = ft_substr(str, 1, i - 1, gc);
		add_token(tokens, TOKEN_DQUOTE, content, gc);
		return (i + 1);
	}
	else
	{
		add_token(tokens, TOKEN_END, NULL, gc);
		ft_putstr_fd("Syntax Error: Unclosed Quotes", 2);
		return (i);
	}
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
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