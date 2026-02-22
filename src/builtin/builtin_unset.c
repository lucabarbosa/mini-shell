/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:01:54 by lbento            #+#    #+#             */
/*   Updated: 2026/02/22 17:10:23 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

static int	is_invalid_env(char *str);
int			command_unset(char **args, t_mshell *shell);

int	command_unset(char **args, t_mshell *shell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (is_invalid_env(args[i]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
			status = 1;
		}
		else
			remove_env_var(args[i], shell);
		i++;
	}
	return (status);
}

static int	is_invalid_env(char *name)
{
	int	i;

	if (!name || !name[0])
		return (1);
	if (ft_isalpha(name[0] && name[0] != '_'))
		return (1);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i] && name[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}
