/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:20:22 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 18:32:24 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	handle_redirect(t_cmd *cmd, t_mshell *shell);
char	*check_path(t_cmd *cmd, t_mshell *shell);
void	exec_child_builtin(t_cmd *cmd, t_mshell *shell);
void	do_execve(char *full_path, t_cmd *cmd, t_mshell *shell);

void	handle_redirect(t_cmd *cmd, t_mshell *shell)
{
	char	*full_path;

	file_redirects(cmd, shell);
	if (!cmd->args || !cmd->args[0])
	{
		clean_shell(shell);
		exit(0);
	}
	exec_child_builtin(cmd, shell);
	full_path = check_path(cmd, shell);
	if (!full_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_shell(shell);
		exit(127);
	}
	do_execve(full_path, cmd, shell);
}

char	*check_path(t_cmd *cmd, t_mshell *shell)
{
	int	err;

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		err = validate_command(cmd->args[0]);
		if (err != 0)
		{
			clean_shell(shell);
			exit(err);
		}
		return (ft_strdup(cmd->args[0], &shell->collector));
	}
	return (get_path(cmd->args[0], shell));
}

void	exec_child_builtin(t_cmd *cmd, t_mshell *shell)
{
	int	ret;

	if (!cmd->args || !cmd->args[0])
		return ;
	if (!is_builtin(cmd->args[0]))
		return ;
	ret = exec_builtin(&cmd, shell);
	clean_shell(shell);
	exit(ret);
}

void	do_execve(char *full_path, t_cmd *cmd, t_mshell *shell)
{
	if (shell->env_char)
		gc_free(&shell->envp_collect, shell->env_char);
	shell->env_char = env_list_to_array(shell->envp, &shell->envp_collect);
	execve(full_path, cmd->args, shell->env_char);
	perror("execve");
	clean_shell(shell);
	exit (126);
}
