/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:44 by lbento            #+#    #+#             */
/*   Updated: 2026/01/14 19:55:39 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;
	t_token		*tokens;

	if (argc != 1 || argv[1])
	{
		printf ("Minishell doesn't get arguments.\n");
		return (1);
	}
	shell.collector = NULL;
	shell.envp = envp;
	tokens = lexer("echo 'hello' | grep hello >> out.txt", &shell.collector);
	print_tokens(tokens);
	gc_clear(&shell.collector);
	return (0);
}
