/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:07 by lbento            #+#    #+#             */
/*   Updated: 2026/02/26 13:45:19 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *name, t_envlist *envp);
void	remove_env_var(char *name, t_mshell *shell);
void	clean_shell(t_mshell *shell);
void	print_error(int num, t_mshell *shell);
void	set_exit(t_mshell *shell);

char	*get_env_value(char *name, t_envlist *envp)
{
	int			len;
	t_envlist	*current;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	current = envp;
	while (current)
	{
		if (ft_strncmp(current->value, name, len) == 0
			&& current->value[len] == '=')
			return (current->value + len + 1);
		current = current->next;
	}
	return (NULL);
}

void	remove_env_var(char *name, t_mshell *shell)
{
	t_envlist	*current;
	t_envlist	*prev;
	int			len;

	prev = NULL;
	current = shell->envp;
	len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp(current->value, name, len) == 0
			&& (current->value[len] == '=' || current->value[len] == '\0'))
		{
			if (prev == NULL)
				shell->envp = current->next;
			else
				prev->next = current->next;
			gc_free(&shell->envp_collect, current->value);
			gc_free(&shell->envp_collect, current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	clean_shell(t_mshell *shell)
{
	gc_clear(&shell->envp_collect);
	gc_clear(&shell->collector);
	close (shell->stdin_backup);
	close (shell->stdout_backup);
	rl_clear_history();
}

void	print_error(int num, t_mshell *shell)
{
	if (num == 1)
	{
		perror("minishell: fork");
		shell->last_exit = 1;
	}
	if (num == 2)
	{
		perror("minishell: dup2");
		shell->last_exit = 1;
	}
	if (num == 3)
	{
		perror("minishell: malloc");
		shell->last_exit = 1;
	}
	if (num == 4)
	{
		ft_putstr_fd("\nminishell: warning: here-document delimited ", 2);
		ft_putstr_fd("by end-of-file\n", 2);
		return ;
	}
	if (num == 5)
		empty_argument_error(shell);
	clean_shell(shell);
	exit (shell->last_exit);
}

void	set_exit(t_mshell *shell)
{
	shell->last_exit = 130;
	g_signal = 0;
}
