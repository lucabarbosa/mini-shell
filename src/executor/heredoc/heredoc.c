/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:18:44 by lbento            #+#    #+#             */
/*   Updated: 2026/02/11 17:37:23 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/heredoc.h"

int			handle_heredocs(t_cmd *cmd, t_mshell *shell);
static int	process_heredoc(t_cmd *current, int index, t_mshell *shell);
static int	heredoc_content(int fd, char *delim, int expand, t_mshell *shell);

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
	int		result;
	int		fd;
	char	*deli;

	deli = parse_delim(current->heredoc_delim, &current->heredoc_expand, shell);
	if (!deli)
		return (1);
	if (!create_temp_file(current, index, shell))
		return (1);
	fd = open(current->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (1);
	}
	result = heredoc_content(fd, deli, current->heredoc_expand, shell);
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
		fill_line(line, fd, expand, shell);
	}
	return (0);
}
