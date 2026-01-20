/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:08:35 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 13:14:34 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

static void		create_pipes(int **pipe,  int num_pipes);
static void		close_pipes(int **pipe,  int num_pipes);
void	exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collector);

void	exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collector)
{
	t_cmd	*current;
	int	pipes[num_cmd - 1][2];
	pid_t	pid[num_cmd];
   int   i;

   i = 0;
   create_pipes(pipes, num_cmd - 1);
	current = cmd;
	while(current)
	{
      pid[i] = fork();
      if (pid[i] == -1)
      {
         perror("fork");
         return ;
      }
		current = current->next;
	}
	close_pipes(pipes, num_cmd - 1);
	i = -1;
	while (i < num_cmd)
		waitpid(pid[i], NULL, 0);
}

static void		create_pipes(int **pipes,  int num_pipes)
{
   int	i;

	i = 0;
	while (i <= num_pipes)
   {
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return ;
		}
      i++;
   }
}

static void		close_pipes(int **pipe,  int num_pipes)
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