/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/02/12 21:00:29 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"
#include "../../includes/builtin.h"

void			executor(t_cmd **cmd, t_mshell *shell);
int				wait_exit_status(pid_t pid);
static void		exec_one_command(t_cmd *cmd, t_cmd **args, t_mshell *shell);

void	executor(t_cmd **cmd, t_mshell *shell)
{
	int		total_cmds;
	t_cmd	*current;

	total_cmds = 0;
	current = *cmd;
	if (handle_heredocs(*cmd, shell))
	{
		shell->last_exit = 130;
		cleanup_heredoc(current);
		return ;
	}
	while (current)
	{
		total_cmds++;
		current = current->next;
	}
	current = *cmd;
	if (total_cmds == 1)
		exec_one_command(current, cmd, shell);
	else
		exec_pipes(total_cmds, current, shell);
	cleanup_heredoc(current);
}

static void	exec_one_command(t_cmd *cmd, t_cmd **args, t_mshell *shell)
{
	pid_t	pid;

	if (cmd->args && cmd->args[0] && parent_built(cmd->args[0]))
	{
		if (exec_builtin(args, shell))
			return ;
	}
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
	sig_wait();
	shell->last_exit = wait_exit_status(pid);
	sig_restore();
}

int	wait_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
