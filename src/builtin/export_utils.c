/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:16:05 by lbento            #+#    #+#             */
/*   Updated: 2026/02/04 19:48:46 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int					export_args(char *arg, t_mshell *shell);
static int			is_valid(char *arg);
static t_envlist	*check_arg_exist(char *arg, int len, t_mshell *shell);
static void			add_new_envp(char *arg, t_mshell *shell);
static void			update_envp(char *arg, t_envlist *found, t_mshell *shell);

int	export_args(char *arg, t_mshell *shell)
{
	t_envlist	*exist;
	int			len;

	if (is_valid(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (0);
	len = 0;
	exist = check_arg_exist(arg, len, shell);
	if (exist)
		update_envp(arg, exist, shell);
	else
		add_new_envp(arg, shell);
	return (0);
}

static int	is_valid(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) && arg[0] != '_')
			return (1);
		i++;
	}
	return (0);
}

static t_envlist	*check_arg_exist(char *arg, int len, t_mshell *shell)
{
	int			i;
	char		*found;
	t_envlist	*current;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	found = ft_substr(arg, 0, i, &shell->collector);
	if (!found)
		return (NULL);
	current = shell->envp;
	len = ft_strlen(found);
	while (current)
	{
		if (ft_strncmp(found, current->value, len) == 0)
		{
			if (current->value[len] == '=' || current->value[len] == '\0')
				return (current);
		}
		current = current->next;
	}
	gc_free(&shell->collector, found);
	return (NULL);
}

static void	add_new_envp(char *arg, t_mshell *shell)
{
	t_envlist	*new_node;
	t_envlist	*current;

	new_node = gc_malloc(&shell->envp_collect, sizeof(t_envlist));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(arg, &shell->envp_collect);
	new_node->next = NULL;
	if (!shell->envp)
	{
		shell->envp = new_node;
		return ;
	}
	current = shell->envp;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void	update_envp(char *arg, t_envlist *found, t_mshell *shell)
{
	gc_free(&shell->envp_collect, found->value);
	found->value = ft_strdup(arg, &shell->envp_collect);
}
