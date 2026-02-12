/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:10:21 by lbento            #+#    #+#             */
/*   Updated: 2026/02/11 21:44:14 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heredoc.h"

void	cleanup_heredoc(t_cmd *cmd);
char	*parse_delim(char *delim, int *expand, t_mshell *shell);
int		create_temp_file(t_cmd *cmd, int index, t_mshell *shell);
int		is_delimiter(char *line, char *delimiter);
void	heredoc_redirects(t_cmd *cmd, t_mshell *shell);

void	cleanup_heredoc(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->heredoc_file != NULL)
			unlink(current->heredoc_file);
		current = current->next;
	}
}

int	create_temp_file(t_cmd *cmd, int index, t_mshell *shell)
{
	char	*i;

	i = ft_itoa(index, &shell->collector);
	if (!i)
		return (0);
	cmd->heredoc_file = ft_strjoin("/tmp/ms_heredoc_", i, &shell->collector);
	gc_free(&shell->collector, i);
	if (!cmd->heredoc_file)
		return (0);
	return (1);
}

char	*parse_delim(char *delim, int *expand, t_mshell *shell)
{
	char	*clean;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	*expand = 1;
	len = ft_strlen(delim);
	clean = gc_malloc(&shell->collector, len + 1);
	if (!clean)
		return (NULL);
	while (delim[i])
	{
		if (delim[i] == '\'' || delim[i] == '"')
			*expand = 0;
		else
		{
			clean[j] = delim[i];
			j++;
		}
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

int	is_delimiter(char *line, char *delimiter)
{
	int	len_line;
	int	len_delim;

	if (!line || !delimiter)
		return (0);
	len_line = ft_strlen (line);
	len_delim = ft_strlen(delimiter);
	if (len_line > 0 && line[len_line - 1] == '\n')
		len_line--;
	if (len_line != len_delim)
		return (0);
	if (ft_strncmp(line, delimiter, len_delim) == 0)
		return (1);
	return (0);
}

void	heredoc_redirects(t_cmd *cmd, t_mshell *shell)
{
	int	fd;

	fd = open(cmd->heredoc_file, O_RDONLY);
	if (fd == -1)
		print_error(0, shell);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close (fd);
		print_error(2, shell);
	}
	close (fd);
}

