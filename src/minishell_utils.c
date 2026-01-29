/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:07 by lbento            #+#    #+#             */
/*   Updated: 2026/01/28 16:28:16 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int num, t_mshell *shell);

void	print_error(int num, t_mshell *shell)
{
	if (num == 1)
		perror("minishell: fork");
	if (num == 2)
		perror("minishell: dup2");
	clean_shell(shell);
	exit (1);
}
