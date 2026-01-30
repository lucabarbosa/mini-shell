/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:01:54 by lbento            #+#    #+#             */
/*   Updated: 2026/01/30 10:57:24 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

static int	is_valid_env(char *str);
int			command_unset(char **args, t_mshell *shell);

int	command_unset(char **args, t_mshell *shell)
{
	int	i;
	int	status;
	int	index;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (is_valid_env(args[i]))
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			status = 1;
		}
		else
		{
			index = find_env_index(args[i], shell->envp);
			if (index != -1)
			{
				remove_env_var(index, shell);
				gc_free(&shell->envp_collect, args[i]);
			}
		}
		i++;
	}
	return (status);
}

static int	is_valid_env(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0] && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i] && name[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
