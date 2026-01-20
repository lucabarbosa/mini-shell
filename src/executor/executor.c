/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 13:09:43 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void			executor(t_gc **collector, char **envp);
static void		exec_one_command(t_cmd *cmd, char **envp);
static void	exec_multi_command(t_cmd *cmd, t_gc **collector, char **envp);

void	executor(t_gc **collector, char **envp)
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
	exec_multi_command(cmd, collector, envp);
}

static void	exec_multi_command(t_cmd *cmd, t_gc **collector, char **envp)
{
	int	total_cmds;
	t_cmd	*current;

	total_cmds = 0;
	current = cmd;
	while (current)
	{
		total_cmds++;
		current = current->next;
	}
	if (total_cmds == 1)
	{
		exec_one_command(cmd, envp);
		return ;
	}
	exec_pipes(total_cmds, cmd, envp, collector);
}

static void	exec_one_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirect(cmd) != 0)
			return ;
		execve(cmd->args[0], cmd->args, envp);
		perror(cmd->args[0]);
		return ;
	}
	waitpid(pid, NULL, 0);
	return ;
}
