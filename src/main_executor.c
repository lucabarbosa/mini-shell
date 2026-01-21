/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:44 by lbento            #+#    #+#             */
/*   Updated: 2026/01/21 13:41:26 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

static t_cmd	**tester_cmd(t_gc **collector);

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
		return (1);
	}
	executor(cmd, &shell);
	gc_clear(&shell.collector);
	return (0);
}

t_cmd	**tester_cmd(t_gc **collector)
{
    t_cmd *cmd;

	 cmd = gc_malloc(collector, sizeof(t_cmd));
    cmd->args = gc_malloc(collector, 3 * sizeof(char *));
    cmd->args[0] = ft_strdup("ls", collector);
    cmd->args[1] = NULL;
    cmd->infile = NULL;
    cmd->outfile = ft_strdup("test.txt", collector);
    cmd->append = 0;

    cmd->next = gc_malloc(collector, sizeof(t_cmd));
    cmd->next->args = gc_malloc(collector, 3 * sizeof(char *));
    cmd->next->args[0] = ft_strdup("ls", collector);
    cmd->next->args[1] = ft_strdup("-l", collector);
    cmd->next->args[2] = NULL;
    cmd->next->infile = ft_strdup("infile.txt", collector);
    cmd->next->outfile = ft_strdup("test.txt", collector);
    cmd->next->append = 0;
    cmd->next->next = NULL;
    return cmd;
}
