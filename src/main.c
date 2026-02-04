/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:40:50 by lbento            #+#    #+#             */
/*   Updated: 2026/02/04 19:17:09 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			init_shell(t_mshell *shell, char **envp);
static t_envlist	*init_envp(char **envp, t_gc **collector);
static int			input_process(char *input, t_mshell *shell);
static void			shell_loop(t_mshell *shell);

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
	shell->envp_collect = NULL;
	shell->env_char = NULL;
	shell->envp = init_envp(envp, &shell->envp_collect);
	if (!shell->envp)
		print_error(3, shell);
	shell->last_exit = 0;
	shell->running = 1;
}

static t_envlist	*init_envp(char **envp, t_gc **collector)
{
	int			i;
	t_envlist	*head;
	t_envlist	*current;
	t_envlist	*new_node;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = gc_malloc(collector, sizeof(t_envlist));
		if (!new_node)
			return (NULL);
		new_node->value = ft_strdup(envp[i], collector);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
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
