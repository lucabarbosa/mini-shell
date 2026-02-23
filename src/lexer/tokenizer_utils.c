/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:19:08 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/22 21:35:23 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_token_type	quote_type(char *str);

int	handle_concat_token(char *str, t_token **tokens, t_gc **gc)
{
	int				i;
	int				expandable;
	char			*result;
	t_token_type	type;

	i = 0;
	result = ft_strdup("", gc);
	expandable = 0;
	type = quote_type(str);
	while (str[i] && str[i] != ' ' && !is_operator(str[i]))
	{
		if (str[i] == '\'')
			i += process_squote(str + i, &result, gc);
		else if (str[i] == '"')
			i += process_dquote(str + i, &result, &expandable, gc);
		else
		{
			i += process_word_part(str + i, &result, &expandable, gc);
			type = TOKEN_WORD;
		}
	}
	add_token(tokens, type, result, gc);
	fill_last_expandable(tokens, expandable);
	return (i);
}

static t_token_type	quote_type(char *str)
{
	int	i;

	if (str[0] != '\'' && str[0] != '"')
		return (TOKEN_WORD);
	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	if (str[i] == str[0] && (!str[i + 1]
			|| str[i + 1] == ' ' || is_operator(str[i + 1])))
	{
		if (str[0] == '\'')
			return (TOKEN_SQUOTE);
		return (TOKEN_DQUOTE);
	}
	return (TOKEN_WORD);
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
