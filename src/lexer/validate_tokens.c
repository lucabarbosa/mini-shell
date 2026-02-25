/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:22:38 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/24 23:48:37 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_invalid_heredoc(t_token *cr);

void	validate_tokens(t_token **token)
{
	t_token	*cr;

	if (!token || !*token)
		return ;
	cr = *token;
	if ((*token)->value[0] == '\0')
	{
		*token = NULL;
		return ;
	}
	else if (has_invalid_heredoc(cr))
	{
		*token = NULL;
		return ;
	}
	else if (cr->type == TOKEN_HEREDOC && cr->next
		&& cr->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		*token = NULL;
	}
}

static int	has_invalid_heredoc(t_token *cr)
{
	while (cr && cr->type != TOKEN_END)
	{
		if (cr->type == TOKEN_HEREDOC && cr->next
			&& (!cr->next->value || !cr->next->value[0]))
			return (1);
		cr = cr->next;
	}
	return (0);
}

void	is_tkn_valid(t_token **tokens)
{
	t_token	*cr;

	cr = *tokens;
	if (cr->type == TOKEN_HEREDOC)
	{
		if (!cr->next || cr->next->type == TOKEN_END)
		{
			*tokens = NULL;
			print_tk_errp(cr->type);
			return ;
		}
		if (!cr->next->value || cr->next->value[0] == '\0')
		{
			*tokens = NULL;
			print_tk_errp(cr->type);
			return ;
		}
	}
	if (cr->type == TOKEN_PIPE || chk_first(cr))
	{
		*tokens = NULL;
		print_tk_errp(cr->type);
		return ;
	}
}

void	print_tk_errp(t_token_type type)
{
	if (type == TOKEN_PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}

int	is_word_start(char c)
{
	return (c != ' ' && !is_operator(c) && c != '\'' && c != '"');
}
