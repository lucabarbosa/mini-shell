/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 19:11:24 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void			executor(t_cmd **cmd, t_mshell *shell);
static int		is_builtin(char *arg);
static void		check_commands(t_cmd **cmd, t_mshell *shell);
static void		exec_one_command(t_cmd *cmd, char **envp);
static void		execution_commands(t_cmd *cmd, t_gc **collector, char **envp);

void	executor(t_cmd **cmd, t_mshell *shell)
{
	int		total_cmds;
	t_cmd	*current;

	total_cmds = 0;
	current = *cmd;
	while (current->next)
	{
		total_cmds++;
		current = current->next;
	}
	current = *cmd;
	check_commands(cmd, &shell->collector);
	if (total_cmds == 1)
	{
		if (is_builtin(current->args[0]))
			exec_builtin(cmd, shell);
		else
			exec_one_command(current, &shell->envp);
	}
	else
		exec_pipes(cmd, total_cmds, &shell->collector, &shell->envp);
}

static void	check_commands(t_cmd **cmd, t_mshell *shell)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
	{
		if (temp)
		{
			if (get_path(temp->args, &shell->collector))
			{
				printf("command not found: %s", temp->args[0]);
				return ;
			}
		}
		temp = temp->next;
	}
}

static void	exec_one_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (handle_one_redirect(cmd) != 0)
			return ;
		execve(cmd->args[0], cmd->args, envp);
		perror(cmd->args[0]);
		return ;
	}
	waitpid(pid, NULL, 0);
	return ;
}

static int	is_builtin(char *arg)
{
	if (!ft_strcmp("echo", arg))
		return (1);
	else if (!ft_strcmp("cd", arg))
		return (1);
	else if (!ft_strcmp("pwd", arg))
		return (1);
	else if (!ft_strcmp("export", arg))
		return (1);
	else if (!ft_strcmp("unset", arg))
		return (1);
	else if (!ft_strcmp("env", arg))
		return (1);
	else if (!ft_strcmp("exit", arg))
		return (1);
	else
		return (0);
}
