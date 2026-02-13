/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:51:22 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 20:38:19 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int			parent_redirect(t_cmd *cmd);
static int	apply_one_redir(t_redir *redir);
static int	open_redir_file(t_redir *redir);
void		parent_restore_fds(int saved_in, int saved_out);

int	parent_redirect(t_cmd *cmd)
{
	t_redir	*current;

	current = cmd->redirects;
	while (current)
	{
		if (apply_one_redir(current))
			return (1);
		current = current->next;
	}
	return (0);
}

static int	apply_one_redir(t_redir *current)
{
	int	fd;
	int	target;

	fd = open_redir_file(current);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(current->file);
		return (1);
	}
	target = STDOUT_FILENO;
	if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_HEREDOC)
		target = STDIN_FILENO;
	if (dup2(fd, target) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	open_redir_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	parent_restore_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
