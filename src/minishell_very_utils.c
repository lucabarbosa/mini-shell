/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_very_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:34:07 by lbento            #+#    #+#             */
/*   Updated: 2026/02/13 17:35:45 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_fds(char *input, t_mshell *shell)
{
	dup2(shell->stdin_backup, 0);
	dup2(shell->stdout_backup, 1);
	free(input);
}
