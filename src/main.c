/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:44 by lbento            #+#    #+#             */
/*   Updated: 2025/12/11 22:40:17 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;
	char		*text;

	if (argc != 2 || !argv[1])
	{
		printf ("Minishell doesn't get arguments.\n");
		return (0);
	}
	shell.collector = NULL;
	shell.envp = envp;
	text = gc_malloc(&shell.collector, sizeof(char) * strlen(argv[1]));
	text = argv[1];
	printf("\n%s\n", text);
	gc_clear(&shell.collector);
	return (0);
}
