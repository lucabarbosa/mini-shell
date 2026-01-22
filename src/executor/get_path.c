/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:05:42 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:00:30 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

char		*get_path(char *cmd, t_gc **collector);
static char	**getting_path(t_gc **collector);
static char	*finding_executable(char *cmd, char **paths, t_gc **collector);

char	*get_path(char *cmd, t_gc **collector)
{
	char	**cmd_paths;
	char	*full_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd, collector));
        else
            return (NULL);
    }
	cmd_paths = getting_path(collector);
	if (!cmd_paths)
		return (NULL);
	full_path = finding_executable(cmd, cmd_paths, collector);
	return (full_path);
}

static char	**getting_path(t_gc **collector)
{
	char	*path_envp;
	char	**all_paths;
	char	*temp;
	int		i;

	path_envp = getenv("PATH");
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
