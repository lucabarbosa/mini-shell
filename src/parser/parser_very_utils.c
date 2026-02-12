/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_very_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:56:05 by lbento            #+#    #+#             */
/*   Updated: 2026/02/12 17:44:41 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_argument(t_cmd *cmd, char *arg, t_gc **collector)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = gc_malloc(collector, sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (i < count)
		{
			new_args[i] = cmd->args[i];
			i++;
		}
	}
	new_args[count] = ft_strdup(arg, collector);
	new_args[count + 1] = NULL;
	cmd->args = new_args;
}

void	add_redir(t_cmd *cmd, int type, char *file, t_gc **collector)
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
	t_redir	*new;
	t_redir	*current;

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
