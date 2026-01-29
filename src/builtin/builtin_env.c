/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:11:28 by lbento            #+#    #+#             */
/*   Updated: 2026/01/29 11:44:54 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int   command_env(char **args, char **envp);

int   command_env(char **args, char **envp)
{
	int   i;

	if (!envp || !envp [0])
		return (1);
	if (args[1] != NULL)
	{
		ft_putendl_fd("minishell: env: command not allowed", 2);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
