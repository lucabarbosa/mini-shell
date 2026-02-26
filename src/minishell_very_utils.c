/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_very_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:34:07 by lbento            #+#    #+#             */
/*   Updated: 2026/02/26 13:46:04 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_shell(t_mshell *shell, char **envp);
t_envlist	*init_envp(char **envp, t_gc **gc, int i);
void		restore_fds(char *input, t_mshell *shell);

void	init_shell(t_mshell *shell, char **envp)
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

t_envlist	*init_envp(char **envp, t_gc **gc, int i)
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

void	restore_fds(char *input, t_mshell *shell)
{
	dup2(shell->stdin_backup, 0);
	dup2(shell->stdout_backup, 1);
	free(input);
}

void	empty_argument_error(t_mshell *shell)
{
	ft_putstr_fd("minishell: : command not found\n", 2);
	clean_shell(shell);
	exit (127);
}
