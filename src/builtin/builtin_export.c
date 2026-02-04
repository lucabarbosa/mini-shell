/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:52:30 by lbento            #+#    #+#             */
/*   Updated: 2026/02/04 17:04:22 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int			command_export(char **args, t_mshell *shell);
static void	print_env(t_envlist *envp, t_mshell *shell);
static void	sort_envp(char **envp);

int	command_export(char **args, t_mshell *shell)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_env(shell->envp, shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (export_args(args[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}

static void	print_env(t_envlist *envp, t_mshell *shell)
{
	char		**envp_array;
	char		*equal_sig;
	int			i;
	int			len;

	if (!shell->envp)
		return ;
	envp_array = env_list_to_array(envp, &shell->envp_collect);
	sort_envp(envp_array);
	i = 0;
	while (envp_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strcmp(envp_array[i], "="))
		{
			equal_sig = ft_strchr(envp_array[i], '=');
			len = equal_sig - envp_array[i];
			write(1, envp_array[i], len + 1);
			printf("\"%s\"\n", equal_sig + 1);
		}
		else
			printf("%s\n", envp_array[i]);
		i++;
	}
	gc_free(&shell->envp_collect, envp_array);
}

static void	sort_envp(char **envp)
{
	int		total;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
		i++;
	total = i;
	i = 0;
	while (i < total - 1)
	{
		j = 0;
		while (j < total - 1 - i)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
