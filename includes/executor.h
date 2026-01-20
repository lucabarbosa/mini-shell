/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:55:25 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 17:56:34 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	**tester_cmd(t_gc **collector);
void	executor(t_cmd **cmd, t_mshell *shell);
int		get_path(char **cmd, t_gc **collector);
int		handle_one_redirect(t_cmd *cmd);
pid_t	*create_pipes_pids(int **pipes, int num_cmd, t_gc **collector);
void	exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collector);

#endif