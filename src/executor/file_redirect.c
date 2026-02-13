/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:12:05 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 18:51:45 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executor.h"

void	file_redirects(t_cmd *cmd, t_mshell *shell);
void	infile_redirect(char *file, t_mshell *shell);
void	outfile_redirect(char *file, int append, t_mshell *shell);

void	file_redirects(t_cmd *cmd, t_mshell *shell)
{
	t_redir	*current_redir;

	current_redir = cmd->redirects;
	while (current_redir)
	{
		if (current_redir->type == TOKEN_REDIR_IN)
			infile_redirect(current_redir->file, shell);
		else if (current_redir->type == TOKEN_REDIR_OUT)
			outfile_redirect(current_redir->file, 0, shell);
		else if (current_redir->type == TOKEN_REDIR_APPEND)
			outfile_redirect(current_redir->file, 1, shell);
		else if (current_redir->type == TOKEN_HEREDOC)
			infile_redirect(current_redir->file, shell);
		current_redir = current_redir->next;
	}
}

void	infile_redirect(char *file, t_mshell *shell)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		clean_shell(shell);
		exit (1);
	}
	if (dup2 (fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close (fd);
		clean_shell (shell);
		exit (1);
	}
	close (fd);
}

void	outfile_redirect(char *file, int append, t_mshell *shell)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		clean_shell(shell);
		exit (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close (fd);
		clean_shell(shell);
		exit (1);
	}
	close (fd);
}
