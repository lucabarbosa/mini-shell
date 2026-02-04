/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:20:22 by lbento            #+#    #+#             */
/*   Updated: 2026/02/04 14:32:52 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void			handle_redirect(t_cmd *cmd, t_mshell *shell);
static int		infile_redirect(t_cmd *cmd, int newfd);
static int		outfile_redirect(t_cmd *cmd, int newfd);

void	handle_redirect(t_cmd *cmd, t_mshell *shell)
{
	char	*full_path;

	if (cmd->infile)
		if (infile_redirect(cmd, STDIN_FILENO))
			print_error (0, shell);
	if (cmd->outfile)
		if (outfile_redirect(cmd, STDOUT_FILENO))
			print_error (0, shell);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		if (exec_builtin(&cmd, shell))
			return ;
	full_path = get_path(cmd->args[0], shell);
	if (!full_path)
	{
		perror(cmd->args[0]);
		clean_shell(shell);
		exit (127);
	}
	if (shell->env_char)
		gc_free(&shell->envp_collect, shell->env_char);
	shell->env_char = env_list_to_array(shell->envp, &shell->envp_collect);
	execve(full_path, cmd->args, shell->env_char);
	perror("execve");
	clean_shell(shell);
	exit (126);
}

static int	infile_redirect(t_cmd *cmd, int newfd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->infile);
		return (1);
	}
	if (dup2 (fd, newfd) == -1)
	{
		perror(cmd->infile);
		close (fd);
		return (1);
	}
	close (fd);
	return (0);
}

static int	outfile_redirect(t_cmd *cmd, int newfd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(cmd->outfile);
		return (1);
	}
	if (dup2(fd, newfd) == -1)
	{
		perror(cmd->outfile);
		close (fd);
		return (1);
	}
	close (fd);
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
