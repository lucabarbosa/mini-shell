/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:20:22 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 11:02:37 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void			handle_redirect(t_cmd *cmd, t_mshell *shell);
static void		infile_redirect(char *file, t_mshell *shell);
static void		outfile_redirect(char *file, int append, t_mshell *shell);
char			**env_list_to_array(t_envlist *envp, t_gc **collector);
static void		file_redirects(t_cmd *cmd, t_mshell *shell);

void	handle_redirect(t_cmd *cmd, t_mshell *shell)
{
	char	*full_path;

	file_redirects(cmd, shell);
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

static void	file_redirects(t_cmd *cmd, t_mshell *shell)
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

static void	infile_redirect(char *file, t_mshell *shell)
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

static void	outfile_redirect(char *file, int append, t_mshell *shell)
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
