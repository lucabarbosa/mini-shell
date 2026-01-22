/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:56:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:30:12 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void			executor(t_cmd **cmd, t_mshell *shell);
static void		exec_one_command(t_cmd *cmd, t_mshell *shell);

int		is_builtin(char *arg);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);

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
			exec_builtin(cmd, shell);
		else
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
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		handle_redirect(cmd, shell);
		exit (1);
	}
	waitpid(pid, NULL, 0);
}

int	is_builtin(char *arg)
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

void	exec_builtin(t_cmd **cmd, t_mshell *shell)
{
	printf("NÃO FOI FEITO ESSE BUILTIN %s\n", cmd[0]->args[0]);
	gc_clear (&shell->collector);
	exit (0);
}
