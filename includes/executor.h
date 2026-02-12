/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:55:25 by lbento            #+#    #+#             */
/*   Updated: 2026/02/12 02:58:55 by lbento           ###   ########.fr       */
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
# include "minishell.h"
# include "builtin.h"
# include "heredoc.h"

typedef struct s_mshell		t_mshell;

typedef struct s_envlist	t_envlist;

typedef struct s_redir
{
	int				type;
	char				*file;
	char				*heredoc_delim;
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir		*redirects;
	struct s_cmd	*next;
}	t_cmd;

int		wait_exit_status(pid_t pid);
void	executor(t_cmd **cmd, t_mshell *shell);
char	*get_path(char *cmd, t_mshell *shell);
void	handle_redirect(t_cmd *cmd, t_mshell *shell);
void	exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell);
char	**env_list_to_array(t_envlist *envp, t_gc **collector);

#endif