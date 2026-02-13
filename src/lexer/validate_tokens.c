/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:22:38 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 20:26:55 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	validate_tokens(t_token **token)
{
	t_token	*cr;

	cr = *token;
	if ((*token)->value[0] == '\0')
		*token = NULL;
	else if (cr->type == TOKEN_HEREDOC && cr->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		*token = NULL;
	}
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
	if (cr->type != TOKEN_WORD && cr->type != TOKEN_HEREDOC)
	{
		*tokens = NULL;
		print_tk_errp(cr->type);
		return ;
	}
	expandable_tokens(*tokens);
}

void	print_tk_errp(t_token_type type)
{
	if (type == TOKEN_PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}
