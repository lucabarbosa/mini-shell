/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:33:21 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/12 03:06:49 by lbento           ###   ########.fr       */
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

void	add_redir(t_cmd *cmd,int type,char *file,t_gc **collector)
{
	t_redir	*new;
	t_redir	*current;
	
	new = gc_malloc(collector, sizeof(t_redir));
	if (!new)
		return ;
	new->file = ft_strdup(file, collector);
	new->type = type;
	new->next = NULL;
	if (!cmd->redirects)
	{
		cmd->redirects = new;
		return ;
	}
	current = cmd->redirects;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_heredoc_redir(t_cmd *cmd, char *delim, int expand, t_gc **collector)
{
    t_redir *new;
    t_redir *current;

    new = gc_malloc(collector, sizeof(t_redir));
    if (!new)
        return ;
    new->type = TOKEN_HEREDOC;
    new->file = NULL;
    new->heredoc_expand = expand;
    new->heredoc_delim = ft_strdup(delim, collector);
    new->next = NULL;
    if (!cmd->redirects)
    {
        cmd->redirects = new;
        return ;
    }
    current = cmd->redirects;
    while (current->next)
        current = current->next;
    current->next = new;
}
