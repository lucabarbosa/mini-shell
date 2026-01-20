/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:20:22 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 19:42:54 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

int			handle_one_redirect(t_cmd *cmd);
static int	infile_redirec(t_cmd *cmd, int newfd);
static int	outfile_redirec(t_cmd *cmd, int newfd);

int	handle_one_redirect(t_cmd *cmd)
{
	int	exit;

	if (cmd->infile)
	{
		exit = infile_redirec(cmd, STDIN_FILENO);
		if (exit)
			return (exit);
	}
	if (cmd->outfile)
	{
		exit = outfile_redirec(cmd, STDOUT_FILENO);
		if (exit)
			return (exit);
	}
	return (0);
}

int	handle_mult_redirect(t_cmd *cmd)
{
	int	exit;

	if (cmd->infile)
	{
		exit = infile_redirec(cmd, STDIN_FILENO);
		if (exit)
			return (exit);
	}
	if (cmd->outfile)
	{
		exit = outfile_redirec(cmd, STDOUT_FILENO);
		if (exit)
			return (exit);
	}
	return (0);
}

static int	infile_redirec(t_cmd *cmd, int newfd)
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

static int	outfile_redirec(t_cmd *cmd, int newfd)
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
