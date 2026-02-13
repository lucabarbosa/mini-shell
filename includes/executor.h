/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:55:25 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 18:58:44 by lbento           ###   ########.fr       */
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
# include <termios.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include "minishell.h"
# include "builtin.h"
# include "heredoc.h"

typedef struct s_mshell		t_mshell;

typedef struct s_envlist	t_envlist;

typedef struct s_redir
{
	int				type;
	char			*file;
	char			*heredoc_delim;
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirects;
	struct s_cmd	*next;
}	t_cmd;

void		exec_pipes(int num_cmd, t_cmd *cmd, t_mshell *shell);

void		executor(t_cmd **cmd, t_mshell *shell);
int			wait_exit_status(pid_t *pid, int num_cmd);
void		exec_parent_builtin(t_cmd *cmd, t_cmd **arg, t_mshell *shell);
void		exec_one_cmd(t_cmd *cmd, t_cmd **arg, int num_cmd, t_mshell *shell);

void		file_redirects(t_cmd *cmd, t_mshell *shell);
void		infile_redirect(char *file, t_mshell *shell);
void		outfile_redirect(char *file, int append, t_mshell *shell);

char		*get_path(char *cmd, t_mshell *shell);

void		handle_redirect(t_cmd *cmd, t_mshell *shell);
char		*check_path(t_cmd *cmd, t_mshell *shell);
void		exec_child_builtin(t_cmd *cmd, t_mshell *shell);
void		do_execve(char *full_path, t_cmd *cmd, t_mshell *shell);

int			parent_redirect(t_cmd *cmd);
void		parent_restore_fds(int saved_in, int saved_out);

int			validate_command(char *cmd);
char		**env_list_to_array(t_envlist *envp, t_gc **collector);

#endif