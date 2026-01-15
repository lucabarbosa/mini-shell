/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/15 16:23:26 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void			executor(t_gc **collector, char **envp);
t_cmd			*tester_cmd(t_gc **collector);
static void		exec_one_command(t_cmd *cmd, char **envp);
static void		exec_multi_command(t_cmd *cmd, char **envp);

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
	if (cmd->append)
		exec_multi_command(cmd, envp);
	else
		exec_one_command(cmd, envp);
}

t_cmd	*tester_cmd(t_gc **collector)
{
	t_cmd	*cmd;

	cmd = gc_malloc(collector, sizeof(t_cmd));
	cmd->args = gc_malloc(collector, 3 * sizeof(char *));
	cmd->args[0] = ft_strdup("cat", collector);
	cmd->args[1] = NULL;
	cmd->infile = ft_strdup("infile.txt", collector);
	cmd->outfile = ft_strdup("test.txt", collector);
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
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

static void	exec_multi_command(t_cmd *cmd, char **envp)
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
