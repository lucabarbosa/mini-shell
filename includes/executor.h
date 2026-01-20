/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:55:25 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 13:09:23 by lbento           ###   ########.fr       */
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
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	struct s_cmd		*next;
}	t_cmd;

t_cmd	*tester_cmd(t_gc **collector);
void	executor(t_gc **collector, char **envp);
int		get_path(char **cmd, t_gc **collector);
int		handle_redirect(t_cmd *cmd);
void	exec_pipes(int num_cmd, t_cmd *cmd, char **envp, t_gc **collector);

#endif