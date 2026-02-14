/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:30:53 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 21:01:53 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "minishell.h"
# include "executor.h"

typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_mshell		t_mshell;
typedef struct s_envlist	t_envlist;

int		is_builtin(char *arg);
int		verify_type(t_redir *cur);
int		parent_built(char *cmd);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);
int		command_echo(char **args);
int		command_pwd(void);
int		command_cd(char **args, t_mshell *shell);
int		command_export(char **args, t_mshell *shell);
int		export_args(char *arg, t_mshell *shell);
int		command_unset(char **args, t_mshell *shell);
int		command_env(char **args, t_envlist *envp);
long	command_exit(char **args, t_mshell *shell);

#endif