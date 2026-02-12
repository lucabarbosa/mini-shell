/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:33:21 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/12 16:57:14 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

int	check_argument_token(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_DQUOTE
		|| type == TOKEN_SQUOTE || type == TOKEN_ENV_VAR);
}

void	add_command_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!new_cmd)
		return ;
	if (*head == NULL)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_cmd;
}
