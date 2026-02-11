/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:18:44 by lbento            #+#    #+#             */
/*   Updated: 2026/02/11 12:55:09 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/heredoc.h"

int			handle_heredocs(t_cmd *cmd, t_mshell *shell);
static int	process_heredoc(t_cmd *current, int index, t_mshell *shell);
static int	heredoc_content(int fd, char *delim, int expand, t_mshell *shell);
void	expand_heredoc(char *line, t_mshell *shell);

int	handle_heredocs(t_cmd *cmd, t_mshell *shell)
{
	t_cmd	*current;
	int		result;
	int		index;

	index = 0;
	current = cmd;
	while (current)
	{
		if (current->heredoc_delim)
		{
			result = process_heredoc(current, index, shell);
			if (result != 0)
				return (result);
		}
		index++;
		current = current->next;
	}
	return (0);
}

static int	process_heredoc(t_cmd *current, int index, t_mshell *shell)
{
	int	result;
	int	fd;
	char *delimiter;

	delimiter = parse_delim(current->heredoc_delim, &current->heredoc_expand, shell);
	if (!delimiter)
		return (1);
	if (!create_temp_file(current, index, shell))
		return (1);
	fd = open(current->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");	
		return (1);
	}
	result = heredoc_content(fd, delimiter, current->heredoc_expand, shell);
	close(fd);
	return (result);
}

static int	heredoc_content(int fd, char *delim, int expand, t_mshell *shell)
{
	char	*line;
	
	while (1)
	{
		write(2, "> ", 2);
		line = get_next_line(0, &shell->collector);
		if (g_signal == SIGINT)
		{
			gc_free(&shell->collector, line);
			g_signal = 0;
			return (1);
		}
		if (!line)
		{
			print_error(4, shell);
			return (0);
		}
		if (is_delimiter(line, delim))
		{
			gc_free(&shell->collector, line);
			return (0);
		}
		if (expand)
			expand_heredoc(line, shell);
		write (fd, line, ft_strlen(line));
		gc_free(&shell->collector, line);
	}
	return (0);
}

void	expand_heredoc(char *line, t_mshell *shell)
{
	int	i;
	char	*var_value;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '$' && line[i+1] == '?')
		{
			var_value = ft_itoa(shell->last_exit, &shell->collector);
			line[i] = var_value[0];
			i += 2;
		}
		if (line[i] == '$')
		{
			line[i] = '>';
		}
		i++;
	}
	shell->last_exit = 0;
}
