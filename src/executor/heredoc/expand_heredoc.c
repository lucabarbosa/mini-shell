/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:35:33 by lbento            #+#    #+#             */
/*   Updated: 2026/02/11 21:25:35 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/heredoc.h"

void		fill_line(char *line, int fd, int expand, t_mshell *shell);
static int	is_char_env(char line);
static char	*expand_heredoc(char *line, t_mshell *shell);
static char	*exit_status(char *result, int *i, t_mshell *shell);
static char	*find_env(char *result, char *line, int *i, t_mshell *shell);

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
	char	temp[2];

	i = 0;
	result = ft_strdup("", &shell->collector);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '$' && line[i + 1] == '?')
			result = exit_status(result, &i, shell);
		else if (line[i] == '$' && line[i + 1] && is_char_env(line[i + 1]))
			result = find_env(result, line, &i, shell);
		else
		{
			temp[0] = line[i];
			temp[1] = '\0';
			result = ft_strjoin(result, temp, &shell->collector);
			i++;	
		}
	}
	result = ft_strjoin(result, "\n", &shell->collector);
	return (result);
}

static char	*exit_status(char *result, int *i, t_mshell *shell)
{
	char	*exit_num;

	exit_num = ft_itoa(shell->last_exit, &shell->collector);
	if (exit_num)
		result = ft_strjoin(result, exit_num, &shell->collector);
	*i += 2;
	return (result);
}

static char	*find_env(char *result, char *line, int *i, t_mshell *shell)
{
	int		k;
	int		j;
	char	*var_name;
	char	*var_value;

	k = *i + 1;
	j = *i + 1;
	while (line[j] && is_char_env(line[j]))
		j++;
	var_name = ft_substr(line, k, j - k, &shell->collector);
	if (!var_name)
		print_error(3, shell);
	var_value = get_env_value(var_name, shell->envp);
	if (var_value)
		result = ft_strjoin(result, var_value, &shell->collector);
	*i = j;	
	gc_free(&shell->collector, var_name);
	return (result);
}

static int	is_char_env(char letter)
{
	if (ft_isalnum(letter) || letter == '_')
		return (1);
	return (0);
}
