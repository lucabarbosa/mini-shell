/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:19:08 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 11:02:53 by iaratang         ###   ########.fr       */
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
		ft_putstr_fd("Syntax Error: Unclosed Quotes", 2);
		return (i);
	}
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}
