/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:44 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 17:55:21 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;
	t_cmd		**cmd;

	if (argc != 1 || argv[1])
	{
		printf ("Minishell doesn't get arguments.\n");
		return (1);
	}
	shell.collector = NULL;
	shell.envp = envp;
	cmd = tester_cmd(&shell.collector);
	if (!cmd)
	{
		printf("Error ----> tester_cmd\n");
		return ;
	}
	executor(cmd, &shell);
	gc_clear(&shell.collector);
	return (0);
}

t_cmd	**tester_cmd(t_gc **collector)
{
	t_cmd	**cmd;

	cmd[0] = gc_malloc(collector, sizeof(t_cmd));
	cmd[0]->args = gc_malloc(collector, 3 * sizeof(char *));
	cmd[0]->args[0] = ft_strdup("cat", collector);
	cmd[0]->args[1] = NULL;
	cmd[0]->infile = NULL;
	cmd[0]->outfile = ft_strdup("test.txt", collector);
	cmd[0]->append = 0;
	cmd[0]->next = cmd[1];

	cmd[1] = gc_malloc(collector, sizeof(t_cmd));
	cmd[1]->args = gc_malloc(collector, 3 * sizeof(char *));
	cmd[1]->args[0] = ft_strdup("ls", collector);
	cmd[1]->args[1] = ft_strdup("-l", collector);
	cmd[1]->infile = ft_strdup("infile.txt", collector);
	cmd[1]->outfile = ft_strdup("test.txt", collector);
	cmd[1]->append = 0;
	cmd[1]->next = NULL;
	return (cmd);
}
