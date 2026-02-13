/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:40:50 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 15:50:41 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			init_shell(t_mshell *shell, char **envp);
static t_envlist	*init_envp(char **envp, t_gc **gc, int i);
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
	sig_init();
	init_shell(&shell, envp);
	shell_loop(&shell);
	clean_shell(&shell);
	return (shell.last_exit);
}

static void	init_shell(t_mshell *shell, char **envp)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->collector = NULL;
	shell->envp_collect = NULL;
	shell->env_char = NULL;
	shell->envp = init_envp(envp, &shell->envp_collect, 0);
	if (!shell->envp)
		print_error(3, shell);
	shell->last_exit = 0;
	shell->running = 1;
}

static t_envlist	*init_envp(char **envp, t_gc **gc, int i)
{
	t_envlist	*head;
	t_envlist	*current;
	t_envlist	*new_node;

	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = gc_malloc(gc, sizeof(t_envlist));
		if (!new_node)
			return (NULL);
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			new_node->value = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(envp[i]
							+ 6) + 1, gc), gc);
		else
			new_node->value = ft_strdup(envp[i], gc);
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
	char				*input;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
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
		dup2(shell->stdin_backup, 0);
		dup2(shell->stdout_backup, 1);
		free(input);
		input = NULL;
		tcsetattr(STDIN_FILENO, 0, &term);
	}
	close (shell->stdin_backup);
	close (shell->stdout_backup);
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
	print_tokens(tokens);
	if (shell->env_char)
		gc_free(&shell->envp_collect, shell->env_char);
	shell->env_char = env_list_to_array(shell->envp, &shell->envp_collect);
	expand(tokens, &shell->collector, shell);
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
