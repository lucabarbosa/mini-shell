/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:10:21 by lbento            #+#    #+#             */
/*   Updated: 2026/02/05 18:16:11 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heredoc.h"

void	cleanup_heredoc(t_cmd *cmd);

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
