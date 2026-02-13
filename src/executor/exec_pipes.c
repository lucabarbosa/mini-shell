/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:08:35 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 11:02:13 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void		exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell);
static int	**create_pipes(int num_pipes, t_gc **collector);
static void	child_pipes(int **pipe, int num_pipe, int cmd_ind, t_mshell *shell);
static void	close_pipes(int **pipe, int num_pipes);
static int	wait_all_exit(pid_t *pid, int num_cmd);

void	exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell)
{
	int		i;
	pid_t	*pids;
	int		**pipes;

	pipes = create_pipes(num_cmd - 1, &shell->collector);
	if (!pipes)
		return ;
	pids = gc_malloc(&shell->collector, sizeof(pid_t) * num_cmd);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			print_error(0, shell);
		if (pids[i] == 0)
		{
			child_pipes(pipes, num_cmd - 1, i, shell);
			handle_redirect(cmd, shell);
			print_error (0, shell);
		}
		cmd = cmd -> next;
		i++;
	}
	close_pipes(pipes, num_cmd - 1);
	sig_wait();
	shell->last_exit = wait_all_exit(pids, num_cmd);
	sig_restore();
}

static int	**create_pipes(int num_pipes, t_gc **collector)
{
	int		**pipes;
	int		i;

	pipes = gc_malloc(collector, num_pipes * sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = gc_malloc(collector, 2 * sizeof(int));
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	child_pipes(int **pipe, int num_pipe, int cmd_ind, t_mshell *shell)
{
	if (cmd_ind > 0)
		if (dup2(pipe[cmd_ind - 1][0], STDIN_FILENO) == -1)
			print_error(1, shell);
	if (cmd_ind < num_pipe)
		if (dup2(pipe[cmd_ind][1], STDOUT_FILENO) == -1)
			print_error(1, shell);
	close_pipes(pipe, num_pipe);
}

static void	close_pipes(int **pipe, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		i++;
	}
}

static int	wait_all_exit(pid_t *pid, int num_cmd)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < num_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			return (128 + WTERMSIG(status));
		}
		i++;
	}
	return (last_status);
}
