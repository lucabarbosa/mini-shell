/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:55:25 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:28:55 by lbento           ###   ########.fr       */
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

typedef struct s_mshell t_mshell;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

void	executor(t_cmd **cmd, t_mshell *shell);
char	*get_path(char *cmd, t_gc **collector);
void	handle_redirect(t_cmd *cmd, t_mshell *shell);
void	exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell);

int		is_builtin(char *arg);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);

#endif