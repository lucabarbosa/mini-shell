/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:18:44 by lbento            #+#    #+#             */
/*   Updated: 2026/02/05 18:22:10 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heredoc.h"

int			handle_heredocs(t_cmd *cmd, int i, t_mshell *shell);
static int	cmd_has_heredoc(t_cmd *current);
static int	process_heredoc(t_cmd *current, int index, t_mshell *shell);

int	handle_heredocs(t_cmd *cmd, int index, t_mshell *shell)
{
	t_cmd	*current;
	int		result;

	current = cmd;
	while (current)
	{
		if (cmd_has_heredoc(current))
		{
			result = process_heredoc(current, index, shell);
			if (result != 0)
				return (result);
		}
		current = current->next;
	}
	return (0);
}

static int	cmd_has_heredoc(t_cmd *current)
{
	if (current == NULL)
		return (0);
	if (current->heredoc_delim != NULL)
		return (1);
	return (0);
}

static int	process_heredoc(t_cmd *current, int index, t_mshell *shell)
{
	char	*i;

	i = ft_itoa(index, &shell->collector);
	current->heredoc_file = ft_strjoin("/tmp/minishell_heredoc_", i, &shell->collector);
	printf("%s", current->heredoc_file);
	return (0);
}
