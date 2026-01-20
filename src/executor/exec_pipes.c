/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:08:35 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 19:59:26 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void		exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collect);
static void	close_pipes(int **pipe, int num_pipes);
pid_t		*create_pipes_pids(int **pipes, int num_cmd, t_gc **collector);
static void	relocate_pipes(int **pipes, int num_cmd, int i);

void	exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collector)
{
	int		**pipes;
	t_cmd	*current;
	pid_t	*pid;
	int		i;

	i = 0;
	pid = create_pipes_pids(pipes, num_cmd, collector);
	current = cmd;
	while (current)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			return ;
		}
		relocate_pipes(pipes, num_cmd, i);
		if (pid[i] == 0)
			if (handle_mult_redirect(current) != 0)
				perror("execve");
		current = current->next;
		i++;
	}
	while (i-- < num_cmd)
		waitpid(pid[i], NULL, 0);
}

static pid_t	*create_pipes_pids(int **pipes, int num_cmd, t_gc **collector)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pipes = gc_malloc(collector, num_cmd * sizeof(int *));
	while (i < num_cmd)
	{
		pipes[i] = gc_malloc(collector, 2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < num_cmd)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
	pid = gc_malloc(collector, num_cmd * sizeof(pid_t));
	return (pid);
}

static void	relocate_pipes(int **pipes, int num_cmd, int i)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_cmd - 1)
		dup2 (pipes[i][1], STDOUT_FILENO);
	while (j < num_cmd - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
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
