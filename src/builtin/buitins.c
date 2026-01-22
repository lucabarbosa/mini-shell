/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:27:58 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:07:54 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtin.h"

int		is_builtin(char *arg);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);

int	is_builtin(char *arg)
{
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
	else
		return (0);
}

void	exec_builtin(t_cmd **cmd, t_mshell *shell)
{
	printf("NÃO FOI FEITO ESSE BUILTIN %s\n", cmd[0]->args[0]);
	gc_clear (shell->collector);
	exit (0);
}
