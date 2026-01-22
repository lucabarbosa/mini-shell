/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:08:35 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:14:19 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void	exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell);
static int	**create_pipes(int num_cmd, t_gc **collector);
static void	child_pipes(int **pipes, int num_pipes, int cmd_index);
static void	close_pipes(int **pipe, int num_pipes);
static void wait_all(pid_t *pid, int num_cmd);

void	exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell)
{
	int	**pipes;
	pid_t	*pids;
	int		i;

	pipes = create_pipes(num_cmd - 1, &shell->collector);
	if (!pipes)
		return ;
	pids = gc_malloc(&shell->collector, sizeof(pid_t) * num_cmd);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			print_error(0);
		if (pids[i] == 0)
		{
			child_pipes(pipes, num_cmd - 1, i);
			handle_redirect(cmd, shell);
			exit (1);
		}
		cmd = cmd -> next;
		i++;
	}
	close_pipes(pipes, num_cmd - 1);
	wait_all(pids, num_cmd);
}

static int	**create_pipes(int num_pipes, t_gc **collector)
{
	int		**pipes;
	int		i;

	pipes = gc_malloc(collector, num_pipes * sizeof(int *));
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = gc_malloc(collector, 2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	child_pipes(int **pipes, int num_pipes, int cmd_index)
{
	if(cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if(cmd_index < num_pipes)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipes, num_pipes);
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

static void wait_all(pid_t *pid, int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
