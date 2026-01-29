/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:40:50 by lbento            #+#    #+#             */
/*   Updated: 2026/01/29 19:32:05 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_shell(t_mshell *shell, char **envp);
static char	**init_envp(char **envp, t_gc **collector, t_mshell *shell);
static int	input_process(char *input, t_mshell *shell);
static void	shell_loop(t_mshell *shell);

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
	clean_shell(&shell);
	return (shell.last_exit);
}

static void	init_shell(t_mshell *shell, char **envp)
{
	shell->collector = NULL;
	shell->envp = init_envp(envp, &shell->collector, shell);
	shell->last_exit = 0;
	shell->running = 1;
}

static char	**init_envp(char **envp, t_gc **collector, t_mshell *shell)
{
	int		i;
	char	**env_clone;

	i = 0;
	while (envp[i])
		i++;
	shell->env_size = i;
	shell->env_capacity = i + 10;
	env_clone = gc_malloc(collector, sizeof(char *) * (i + 10));
	if (!env_clone)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_clone[i] = ft_strdup(envp[i], collector);
		i++;
	}
	env_clone[i] = NULL;
	return (env_clone);
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
		input = NULL;
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

