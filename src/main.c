/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:40:50 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 19:06:36 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_shell(t_mshell *shell, char **envp);
static int	input_process(char *input, t_mshell *shell);
static void	shell_loop(t_mshell *shell);
static void	cleanup_shell(t_mshell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("minishell: does not accept arguments\n", 2);
		return (1);
	}
	init_shell(&shell, envp);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_exit);
}

static void	init_shell(t_mshell *shell, char **envp)
{
	shell->collector = NULL;
	shell->envp = envp;
	shell->last_exit = 0;
	shell->running = 1;
}

static void	shell_loop(t_mshell *shell)
{
	char	*input;

	while (shell->running)
	{
		input = readline("minishell$> ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			shell->last_exit = input_process(input, shell);
		}
		free(input);
	}
}

static int	input_process(char *input, t_mshell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;
	int		exit_status;

	exit_status = 0;
	tokens = lexer(input, &shell->collector);
	if (tokens == NULL)
	{
		gc_clear(&shell->collector);
		return (1);
	}
	commands = parser(tokens, &shell->collector);
	if (commands == NULL)
	{
		gc_clear(&shell->collector);
		return (1);
	}
	executor(&commands, shell);
	exit_status = shell->last_exit;
	gc_clear(&shell->collector);
	return (exit_status);
}

static void	cleanup_shell(t_mshell *shell)
{
	gc_clear(&shell->collector);
	rl_clear_history();
}
