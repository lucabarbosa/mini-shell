/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:11:28 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 16:45:13 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int	command_env(char **args, t_envlist *envp);

int	command_env(char **args, t_envlist *envp)
{
	t_envlist	*current;

	if (args[1] != NULL)
	{
		ft_putendl_fd("minishell: env: command not allowed", 2);
		return (1);
	}
	current = envp;
	while (current)
	{
		if (ft_strchr(current->value, '='))
			printf("%s\n", current->value);
		current = current->next;
	}
	return (0);
}
