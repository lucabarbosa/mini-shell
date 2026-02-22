/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:46:18 by lbento            #+#    #+#             */
/*   Updated: 2026/02/22 16:50:00 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

static int	have_char(char *str);
long		command_exit(char **args, t_mshell *shell);

long	command_exit(char **args, t_mshell *shell)
{
	long	exit_num;

	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		shell->running = 0;
		return (shell->last_exit);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (have_char(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		shell->running = 0;
		return (2);
	}
	exit_num = ft_atol(args[1]);
	shell->running = 0;
	exit_num = (exit_num % 256 + 256) % 256;
	return (exit_num);
}

static int	have_char(char *str)
{
	int	i;

	if (!str || !str[0])
		return (1);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}
