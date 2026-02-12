/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:10:21 by lbento            #+#    #+#             */
/*   Updated: 2026/02/12 17:49:18 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heredoc.h"

void	cleanup_heredoc(t_cmd *cmd);
int		create_temp_file(t_redir *current, int index, t_mshell *shell);
int		is_delimiter(char *line, char *delimiter);

void	cleanup_heredoc(t_cmd *cmd)
{
	t_cmd		*current;
	t_redir		*redir;

	current = cmd;
	while (current)
	{
		redir = current->redirects;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC && redir->file)
				unlink(redir->file);
			redir = redir->next;
		}
		current = current->next;
	}
}

int	create_temp_file(t_redir *current, int index, t_mshell *shell)
{
	char	*i;

	i = ft_itoa(index, &shell->collector);
	if (!i)
		return (0);
	current->file = ft_strjoin("/tmp/ms_heredoc_", i, &shell->collector);
	gc_free(&shell->collector, i);
	if (!current->file)
		return (0);
	return (1);
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
