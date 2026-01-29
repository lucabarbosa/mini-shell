/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:27:58 by lbento            #+#    #+#             */
/*   Updated: 2026/01/29 19:45:38 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int		is_builtin(char *arg);
int		parent_built(char *arg);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strcmp("echo", arg))
		return (1);
	else if (!ft_strcmp("cd", arg))
		return (1);
	else if (!ft_strcmp("pwd", arg))
		return (1);
	else if (!ft_strcmp("export", arg))
		return (1);
	else if (!ft_strcmp("unset", arg))
		return (1);
	else if (!ft_strcmp("env", arg))
		return (1);
	else if (!ft_strcmp("exit", arg))
		return (1);
	return (0);
}

int	parent_built(char *arg)
{
	if (!arg)
		return (0);
	else if (!ft_strcmp("cd", arg))
		return (1);
	else if (!ft_strcmp("export", arg))
		return (1);
	else if (!ft_strcmp("unset", arg))
		return (1);
	else if (!ft_strcmp("exit", arg))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd **cmd, t_mshell *shell)
{
	char	*command;

	if (!cmd || !*cmd || !(*cmd)->args || !(*cmd)->args[0])
		return ;
	command = (*cmd)->args[0];
	if (!ft_strcmp("echo", command))
		shell->last_exit = command_echo((*cmd)->args);
	else if (!ft_strcmp("cd", command))
		shell->last_exit = 0;
	else if (!ft_strcmp("pwd", command))
		shell->last_exit = command_pwd();
	else if (!ft_strcmp("export", command))
		shell->last_exit = 0;
	else if (!ft_strcmp("unset", command))
		shell->last_exit = command_unset((*cmd)->args, shell);
	else if (!ft_strcmp("env", command))
		shell->last_exit = command_env((*cmd)->args, shell->envp);
	else if (!ft_strcmp("exit", command))
		shell->last_exit = command_exit((*cmd)->args, shell);
}
