/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:07 by lbento            #+#    #+#             */
/*   Updated: 2026/01/29 19:32:53 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *name, char **envp);
int		find_env_index(char *name, char **envp);
void	remove_env_var(int index, t_mshell *shell);
void	clean_shell(t_mshell *shell);
void	print_error(int num, t_mshell *shell);

char	*get_env_value(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	find_env_index(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env_var(int index, t_mshell *shell)
{
	int	i;

	i = index;
	while (shell->envp[i + 1])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = NULL;
	shell->env_size--;
}

void	clean_shell(t_mshell *shell)
{
	gc_clear(&shell->collector);
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
	clean_shell(shell);
	exit (shell->last_exit);
}
