/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/02/26 13:37:08 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"
#include "../../includes/builtin.h"

void		exec_one_cmd(t_cmd *cmd, t_cmd **arg, int num_cmd, t_mshell *shell);
void		executor(t_cmd **cmd, t_mshell *shell);
int			wait_exit_status(pid_t *pid, int num_cmd);
void		exec_parent_builtin(t_cmd *cmd, t_cmd **arg, t_mshell *shell);
static int	check_empty_arg(t_cmd *cmd, t_cmd **arg, t_mshell *shell);

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
		exec_one_cmd(current, cmd, total_cmds, shell);
	else
		exec_pipes(total_cmds, current, shell);
	sig_init();
	cleanup_heredoc(current);
}

void	exec_one_cmd(t_cmd *cmd, t_cmd **arg, int num_cmd, t_mshell *shell)
{
	pid_t	pid;

	if (check_empty_arg(cmd, arg, shell))
		return ;
	if (cmd->args && cmd->args[0] && parent_built(cmd->args[0]))
	{
		exec_parent_builtin(cmd, arg, shell);
		return ;
	}
	pid = fork();
	if (pid == -1)
		print_error(1, shell);
	if (pid == 0)
	{
		sig_child();
		handle_redirect(cmd, shell);
	}
	sig_wait();
	shell->last_exit = wait_exit_status(&pid, num_cmd);
}

static int	check_empty_arg(t_cmd *cmd, t_cmd **arg, t_mshell *shell)
{
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->redirects)
			exec_parent_builtin(cmd, arg, shell);
		return (1);
	}
	if (!cmd->args[0][0])
	{
		if (cmd->redirects)
			exec_parent_builtin(cmd, arg, shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->last_exit = 127;
		return (1);
	}
	return (0);
}

void	exec_parent_builtin(t_cmd *cmd, t_cmd **arg, t_mshell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (cmd->redirects && parent_redirect(cmd))
	{
		parent_restore_fds(saved_in, saved_out);
		shell->last_exit = 1;
		return ;
	}
	exec_builtin(arg, shell);
	parent_restore_fds(saved_in, saved_out);
}

int	wait_exit_status(pid_t *pid, int num_cmd)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < num_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (i == num_cmd - 1)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
				last_status = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (last_status);
}
