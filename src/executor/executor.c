/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/14 19:19:57 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void	executor(t_gc **collector);
t_cmd	*tester_cmd(t_gc **collector);
//int		exec_one_command(t_cmd *cmd);
int i;

void	executor(t_gc **collector)
{
	t_cmd	*cmd;

	cmd = tester_cmd(collector);
	if (!cmd)
	{
		printf("Error ----> tester_cmd\n");
		return ;
	}
	if (get_path(cmd->args, collector))
	{
		printf("command not found: %s", cmd->args[0]);
		return ;
	}
	i = 0;
	while (cmd->args[i])
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
	// result = exec_one_command(cmd);
}

t_cmd	*tester_cmd(t_gc **collector)
{
	t_cmd	*cmd;

	cmd = gc_malloc(collector, sizeof(t_cmd));
	cmd->args = gc_malloc(collector, 2 * sizeof(char *));
	cmd->args[0] = ft_strdup("ls", collector);
	cmd->args[1] = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

// int	exec_one_command(t_cmd *cmd)
// {
// }
