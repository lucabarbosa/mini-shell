/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:19:08 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 12:56:34 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	handle_concat_token(char *str, t_token **tokens, t_gc **gc)
{
	int		i;
	int		expandable;
	char	*result;

	i = 0;
	result = ft_strdup("", gc);
	expandable = 0;
	while (str[i] && str[i] != ' ' && !is_operator(str[i]))
	{
		if (str[i] == '\'')
			i += process_squote(str + i, &result, gc);
		else if (str[i] == '"')
			i += process_dquote(str + i, &result, &expandable, gc);
		else
			i += process_word_part(str + i, &result, &expandable, gc);
	}
	add_token(tokens, TOKEN_WORD, result, gc);
	if (expandable)
		(*tokens)->expandable = 1;
	return (i);
}

int	process_squote(char *str, char **result, t_gc **gc)
{
	int		i;
	char	*content;
	char	*temp;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
	{
		content = ft_substr(str, 1, i - 1, gc);
		temp = *result;
		*result = ft_strjoin(temp, content, gc);
		return (i + 1);
	}
	else
	{
		ft_putstr_fd("Syntax Error: Unclosed Quotes\n", 2);
		return (i);
	}
}

int	process_dquote(char *str, char **result, int *expandable, t_gc **gc)
{
	int		i;
	char	*content;
	char	*temp;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '"')
	{
		content = ft_substr(str, 1, i - 1, gc);
		temp = *result;
		*result = ft_strjoin(temp, content, gc);
		if (ft_strchr(content, '$'))
			*expandable = 1;
		return (i + 1);
	}
	else
	{
		ft_putstr_fd("Syntax Error: Unclosed Quotes\n", 2);
		return (i);
	}
}

int	process_word_part(char *str, char **result, int *expandable, t_gc **gc)
{
	int		i;
	char	*content;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != ' ' && !ft_is_metachar(str[i]))
		i++;
	content = ft_substr(str, 0, i, gc);
	temp = *result;
	*result = ft_strjoin(temp, content, gc);
	if (ft_strchr(content, '$'))
		*expandable = 1;
	return (i);
}

int	is_word_start(char c)
{
	return (c != ' ' && !is_operator(c) && c != '\'' && c != '"');
}
