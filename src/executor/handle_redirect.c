/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:20:22 by lbento            #+#    #+#             */
/*   Updated: 2026/01/28 16:53:54 by lbento           ###   ########.fr       */
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
	{
		exec_builtin(&cmd, shell);
		print_error(0, shell);
	}
	full_path = get_path(cmd->args[0], &shell->collector);
	if (!full_path)
	{
		perror(cmd->args[0]);
		clean_shell(shell);
		exit (127);
	}
	execve(full_path, cmd->args, shell->envp);
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
