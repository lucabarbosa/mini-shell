/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 19:02:16 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"
#include "../../includes/builtin.h"

void			executor(t_cmd **cmd, t_mshell *shell);
int				wait_exit_status(pid_t pid);
static void		exec_one_command(t_cmd *cmd, t_mshell *shell);

void	executor(t_cmd **cmd, t_mshell *shell)
{
	int		total_cmds;
	t_cmd	*current;

	total_cmds = 0;
	current = *cmd;
	while (current)
	{
		total_cmds++;
		current = current->next;
	}
	current = *cmd;
	if (total_cmds == 1)
	{
		if (is_builtin(current->args[0]))
		{
			exec_builtin(cmd, shell);
			return ;
		}
		exec_one_command(current, shell);
	}
	else
		exec_pipes(total_cmds, current, shell);
}

static void	exec_one_command(t_cmd *cmd, t_mshell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->last_exit = 1;
		return ;
	}
	if (pid == 0)
	{
		handle_redirect(cmd, shell);
		exit (1);
	}
	shell->last_exit = wait_exit_status(pid);
}

int	wait_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
