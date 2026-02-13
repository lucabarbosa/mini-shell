/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:05:42 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 17:51:45 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

char		*get_path(char *cmd, t_mshell *shell);
static char	**getting_path(t_envlist *envp, t_gc **collector);
static char	*finding_executable(char *cmd, char **paths, t_gc **collector);

char	*get_path(char *cmd, t_mshell *shell)
{
	char	**cmd_paths;
	char	*full_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd, &shell->collector));
		else
			return (NULL);
	}
	cmd_paths = getting_path(shell->envp, &shell->collector);
	if (!cmd_paths)
		return (NULL);
	full_path = finding_executable(cmd, cmd_paths, &shell->collector);
	return (full_path);
}

static char	**getting_path(t_envlist *envp, t_gc **collector)
{
	char	*path_envp;
	char	**all_paths;
	char	*temp;
	int		i;

	path_envp = get_env_value("PATH", envp);
	if (!path_envp)
		return (NULL);
	all_paths = ft_split(path_envp, ':', collector);
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/", collector);
		if (!temp)
			return (NULL);
		gc_free(collector, all_paths[i]);
		all_paths[i] = temp;
		i++;
	}
	return (all_paths);
}

static char	*finding_executable(char *cmd, char **paths, t_gc **collector)
{
	char	*executable;
	int		i;

	i = 0;
	while (paths[i])
	{
		executable = ft_strjoin(paths[i], cmd, collector);
		if (!executable)
			return (NULL);
		if (access(executable, X_OK) == 0)
			return (executable);
		gc_free(collector, executable);
		i++;
	}
	return (NULL);
}
