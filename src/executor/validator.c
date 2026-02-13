/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:59:23 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 18:18:23 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"
#include <sys/stat.h>

static int	validate_directory(char *path);
int			validate_command(char *cmd);
char		**env_list_to_array(t_envlist *envp, t_gc **collector);

static int	validate_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	validate_command(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (validate_directory(cmd))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

char	**env_list_to_array(t_envlist *envp, t_gc **collector)
{
	t_envlist	*current;
	char		**envp_array;
	int			count;
	int			i;

	count = 0;
	current = envp;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp_array = gc_malloc(collector, sizeof(char *) * (count + 1));
	if (!envp_array)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		envp_array[i] = current->value;
		current = current->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}
