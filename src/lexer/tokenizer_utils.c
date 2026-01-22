/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:19:08 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/22 19:11:45 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	handle_words(char *str, t_token **tokens, t_gc **collector)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != ' ' && !is_metachar(str[i]))
		i++;
	word = ft_substr(str, 0, i, collector);
	add_token(tokens, TOKEN_WORD, word, collector);
	return (i);
}

int	handle_squotes(char *str, t_token **tokens, t_gc **collector)
{
	int		i;
	char	*content;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
	{
		content = ft_substr(str, 1, i - 1, collector);
		add_token(tokens, TOKEN_SQUOTE, content, collector);
		return (i + 1);
	}
	else
		return (-1);
}

int	handle_dquotes(char *str, t_token **tokens, t_gc **collector)
{
	int		i;
	char	*content;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '"')
	{
		content = ft_substr(str, 1, i - 1, collector);
		add_token(tokens, TOKEN_DQUOTE, content, collector);
		return (i + 1);
	}
	else
		return (-1);
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}
