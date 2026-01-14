/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:44 by lbento            #+#    #+#             */
/*   Updated: 2026/01/14 17:47:02 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	if (argc != 1 || argv[1])
	{
		printf ("Minishell doesn't get arguments.\n");
		return (1);
	}
	shell.collector = NULL;
	shell.envp = envp;
	executor(&shell.collector);
	gc_clear(&shell.collector);
	return (0);
}
