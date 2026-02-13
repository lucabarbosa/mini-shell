/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:59:23 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 19:40:14 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"
#include <sys/stat.h>

int			validate_command(char *cmd);
static int	validate_directory(char *path);
static int	is_dot(char *cmd);
static int	is_double_dot(char *cmd);

char		**env_list_to_array(t_envlist *envp, t_gc **collector);

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
		return (126);
	if (is_dot(cmd))
		return (2);
	if (is_double_dot(cmd))
		return (127);
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

static int	validate_directory(char *path)
{
	int			i;
	struct stat	path_stat;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
		{
			if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(path, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	is_dot(char *cmd)
{
	if (cmd[0] == '.' && !cmd[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static int	is_double_dot(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '.')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
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
