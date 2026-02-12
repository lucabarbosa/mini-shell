/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:50:17 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/12 03:03:34 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parser(t_token *tokens, t_gc **collector)
{
	t_cmd	*commands;
	t_cmd	*new_cmd;
	t_token	*current;

	commands = NULL;
	current = tokens;
	while (current && current->type != TOKEN_END)
	{
		new_cmd = parse_command(&current, collector);
		if (new_cmd)
			add_command_to_list(&commands, new_cmd);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (commands);
}

t_cmd	*parse_command(t_token **current, t_gc **collector)
{
	t_cmd	*command;

	command = init_cmd(collector);
	while (*current && (*current)->type != TOKEN_PIPE
		&& (*current)->type != TOKEN_END)
	{
		if (check_redirection_token((*current)->type))
			handle_redirection(command, current, collector);
		else if ((*current)->type == TOKEN_HEREDOC)
			handle_heredoc(command, current, collector);	
		else if (check_argument_token((*current)->type))
		{
			add_argument(command, (*current)->value, collector);
			*current = (*current)->next;
		}
		else
			*current = (*current)->next;
	}
	return (command);
}

t_cmd	*init_cmd(t_gc **collector)
{
	t_cmd	*command;

	command = gc_malloc(collector, sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->redirects = NULL;
	command->next = NULL;
	return (command);
}

int	handle_redirection(t_cmd *cmd, t_token **current, t_gc **collector)
{
	t_token_type	type;

	type = (*current)->type;
	*current = (*current)->next;
	if (!(*current) || ((*current)->type != TOKEN_DQUOTE && (*current)->type
			!= TOKEN_SQUOTE && (*current)->type != TOKEN_WORD))
		return (0);
//-------------------------------------------------------------------------
	// if (type == TOKEN_REDIR_IN)
	// 	cmd->infile = ft_strdup((*current)->value, collector);
	// else if (type == TOKEN_REDIR_OUT)
	// {
	// 	cmd->outfile = ft_strdup((*current)->value, collector);
	// 	cmd->append = 0;
	// }
	// else if (type == TOKEN_REDIR_APPEND)
	// {
	// 	cmd->outfile = ft_strdup((*current)->value, collector);
	// 	cmd->append = 1;
	// }
//------------------------------------------------------------------------
	add_redir(cmd, type, (*current)->value, collector);
	*current = (*current)->next;
	return (1);
}

int	handle_heredoc(t_cmd *cmd, t_token **tokens, t_gc **collector)
{
	t_token			*cr;
	t_token_type	type;
	int				expand;

	cr = (*tokens)->next;
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
	type = cr->type;
	if (type != TOKEN_DQUOTE && type != TOKEN_SQUOTE && type != TOKEN_WORD)
		return (0);
	expand = 1;
	if (type == TOKEN_DQUOTE || type == TOKEN_SQUOTE)
		expand = 0;
	add_heredoc_redir(cmd, cr->value, expand, collector);
	return (1);
}


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
