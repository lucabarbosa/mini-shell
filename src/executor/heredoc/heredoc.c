/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:18:44 by lbento            #+#    #+#             */
/*   Updated: 2026/02/24 14:58:12 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/heredoc.h"

int			handle_heredocs(t_cmd *cmd, t_mshell *shell);
static int	process_heredoc(t_redir *current, int index, t_mshell *shell);
static void	disable_ctl(struct termios *original);
static int	heredoc_content(int fd, char *delim, int expand, t_mshell *shell);
static void	fix_signals(char *line, t_mshell *shell);

int	handle_heredocs(t_cmd *cmd, t_mshell *shell)
{
	t_cmd		*current;
	t_redir		*redir;
	int			index;
	int			result;

	index = 0;
	current = cmd;
	while (current)
	{
		redir = current->redirects;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				g_signal = HEREDOC;
				result = process_heredoc(redir, index, shell);
				if (result != 0)
					return (result);
				index++;
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

static int	process_heredoc(t_redir *current, int index, t_mshell *shell)
{
	int				result;
	int				fd;
	char			*deli;
	struct termios	original;

	deli = current->heredoc_delim;
	if (!deli)
		return (1);
	if (create_temp_file(current, index, shell))
		return (1);
	fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (1);
	}
	tcgetattr(STDIN_FILENO, &original);
	disable_ctl(&original);
	result = heredoc_content(fd, deli, current->heredoc_expand, shell);
	tcsetattr(STDIN_FILENO, TCSANOW, &original);
	sig_init();
	close(fd);
	return (result);
}

static int	heredoc_content(int fd, char *delim, int expand, t_mshell *shell)
{
	char	*line;

	g_signal = HEREDOC;
	while (1)
	{
		write(2, "> ", 2);
		line = get_next_line(0, &shell->collector);
		if (g_signal == SIGINT)
		{
			fix_signals(line, shell);
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

static void	fix_signals(char *line, t_mshell *shell)
{
	gc_free(&shell->collector, line);
	g_signal = 0;
	shell->last_exit = 130;
}

static void	disable_ctl(struct termios *original)
{
	struct termios	modified;

	modified = *original;
	modified.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &modified);
}
