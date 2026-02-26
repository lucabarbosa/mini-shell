/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:40:50 by lbento            #+#    #+#             */
/*   Updated: 2026/02/26 14:00:11 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			input_process(char *input, t_mshell *shell);
void		shell_loop(t_mshell *shell);
void		cmd_executor(t_token *tokens, t_mshell *shell);

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

void	shell_loop(t_mshell *shell)
{
	char				*input;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	while (shell->running)
	{
		input = readline("minishell$> ");
		if (g_signal == CTRL_C)
			set_exit(shell);
		if (input == NULL)
		{
			write (1, "exit\n", 5);
			break ;
		}
		if (input[0] != '\0')
		{
			add_history(input);
			shell->last_exit = input_process(input, shell);
		}
		restore_fds(input, shell);
		input = NULL;
		tcsetattr(STDIN_FILENO, 0, &term);
	}
}

int	input_process(char *input, t_mshell *shell)
{
	t_token	*tokens;
	int		exit_status;

	exit_status = 0;
	tokens = lexer(input, &shell->collector, 0);
	if (tokens == NULL)
	{
		gc_clear(&shell->collector);
		return (2);
	}
	if (shell->env_char)
		gc_free(&shell->envp_collect, shell->env_char);
	shell->env_char = env_list_to_array(shell->envp, &shell->envp_collect);
	expand(tokens, &shell->collector, shell);
	remove_empty_expanded(&tokens);
	if (tokens == NULL || tokens->type == TOKEN_END)
	{
		gc_clear(&shell->collector);
		return (0);
	}
	cmd_executor(tokens, shell);
	exit_status = shell->last_exit;
	gc_clear(&shell->collector);
	return (exit_status);
}

void	cmd_executor(t_token *tokens, t_mshell *shell)
{
	t_cmd	*commands;

	commands = parser(tokens, &shell->collector);
	if (commands == NULL)
	{
		gc_clear(&shell->collector);
		shell->last_exit = 1;
		return ;
	}
	executor(&commands, shell);
}
