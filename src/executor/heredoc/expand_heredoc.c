/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:35:33 by lbento            #+#    #+#             */
/*   Updated: 2026/02/11 18:38:59 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/heredoc.h"

void		fill_line(char *line, int fd, int expand, t_mshell *shell);
static int	is_env(char line);
static char	*expand_heredoc(char *line, t_mshell *shell);
static int	print_exit_status(char *result, int i, t_mshell *shell);
static int	find_env(char *result, char *line, int i, t_mshell *shell);

void	fill_line(char *line, int fd, int expand, t_mshell *shell)
{
	char	*output;

	output = line;
	if (expand)
		output = expand_heredoc(line, shell);
	write (fd, output, ft_strlen(output));
	gc_free(&shell->collector, line);
}

static char	*expand_heredoc(char *line, t_mshell *shell)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '$' && line[i + 1] == '?')
			i = print_exit_status(result, i, shell);
		if (line[i] == '$' && line[i + 1] && is_env(line[i + 1]))
			i = find_env(result, line, i, shell);
		else
			result[i] = line[i];
		i++;
	}
	result = ft_strjoin(result, "\n", &shell->collector);
	return (result);
}

static int	print_exit_status(char *result, int i, t_mshell *shell)
{
	char	*exit_num;

	exit_num = ft_itoa(shell->last_exit, &shell->collector);
	if (!exit_num)
		print_error(3, shell);
	if (result)
	{
		if (exit_num)
			result = ft_strjoin(result, exit_num, &shell->collector);
	}
	else
	{
		if (exit_num)
			result = ft_strdup(exit_num, &shell->collector);
	}
	gc_free(&shell->collector, exit_num);
	return (i + 2);
}

static int	find_env(char *result, char *line, int i, t_mshell *shell)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = i + 1;
	while (line[i] && is_env(line[i]))
		i++;
	var_name = ft_substr(line, j, i - j, &shell->collector);
	if (!var_name)
		print_error(3, shell);
	var_value = get_env_value(var_name, shell->envp);
	if (result)
	{
		if (var_value)
			result = ft_strjoin(result, var_value, &shell->collector);
	}
	else
	{
		if (var_value)
			result = ft_strdup(var_value, &shell->collector);
	}
	gc_free(&shell->collector, var_name);
	return (i);
}

static int	is_env(char letter)
{
	return (ft_isalnum(letter) || letter == '_');
}
