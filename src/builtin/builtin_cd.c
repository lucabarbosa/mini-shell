/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:31:07 by lbento            #+#    #+#             */
/*   Updated: 2026/02/04 13:54:43 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int			command_cd(char **args, t_mshell *shell);
static char	*get_target_path(char **args, int *print, t_mshell *shell);
static void	update_pwd(t_mshell *shell);
static void	update_oldpwd(char *old_pwd, t_mshell *shell);
static void	create_envp_var(char *name, char *new_env, t_mshell *shell);

int	command_cd(char **args, t_mshell *shell)
{
	int		print;
	char	*target;
	char	old_pwd[4096];

	print = 0;
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (getcwd(old_pwd, 4096) == NULL)
		old_pwd[0] = '\0';
	target = get_target_path(args, &print, shell);
	if (target == NULL)
		return (1);
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	if (print)
		printf("%s\n", target);
	update_pwd(shell);
	update_oldpwd(old_pwd, shell);
	return (0);
}

static char	*get_target_path(char **args, int *print, t_mshell *shell)
{
	char	*target;

	if (!args[1] || args[1][0] == '~')
	{
		target = get_env_value("HOME", shell->envp);
		if (!target || !target [0])
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		target = get_env_value("OLDPWD", shell->envp);
		if (!target || !target [0])
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		*print = 1;
	}
	else
		target = args[1];
	return (target);
}

static void	update_pwd(t_mshell *shell)
{
	char		new_pwd[4096];
	char		*temp;
	t_envlist	*current;

	if (getcwd(new_pwd, 4096) == NULL)
		return ;
	current = shell->envp;
	while (current)
	{
		if (ft_strncmp(current->value, "PWD", 3) == 0
			&& current->value[3] == '=')
		{
			gc_free(&shell->envp_collect, current->value);
			temp = ft_strjoin("PWD", "=", &shell->envp_collect);
			current->value = ft_strjoin(temp, new_pwd, &shell->envp_collect);
			gc_free(&shell->envp_collect, temp);
			return ;
		}
		current = current->next;
	}
	create_envp_var("PWD", new_pwd, shell);
}

static void	update_oldpwd(char *old_pwd, t_mshell *shell)
{
	char		*temp;
	t_envlist	*current;

	if (old_pwd[0] == '\0')
		return ;
	current = shell->envp;
	while (current)
	{
		if (ft_strncmp(current->value, "OLDPWD", 6) == 0
			&& current->value[6] == '=')
		{
			gc_free(&shell->envp_collect, current->value);
			temp = ft_strjoin("OLDPWD", "=", &shell->envp_collect);
			current->value = ft_strjoin(temp, old_pwd, &shell->envp_collect);
			gc_free(&shell->envp_collect, temp);
			return ;
		}
		current = current->next;
	}
	create_envp_var("OLDPWD", old_pwd, shell);
}

static void	create_envp_var(char *name, char *set_env, t_mshell *shell)
{
	t_envlist	*new_node;
	char		*temp;

	new_node = gc_malloc(&shell->envp_collect, sizeof(t_envlist));
	if (!new_node)
		print_error(3, shell);
	temp = ft_strjoin(name, "=", &shell->envp_collect);
	new_node->value = ft_strjoin(temp, set_env, &shell->envp_collect);
	gc_free(&shell->envp_collect, temp);
	new_node->next = shell->envp;
	shell->envp = new_node;
}
