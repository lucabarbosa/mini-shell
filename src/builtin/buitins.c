/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:27:58 by lbento            #+#    #+#             */
/*   Updated: 2026/01/20 18:36:21 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_cmd **cmd, t_mshell *shell);

void	exec_builtin(t_cmd **cmd, t_mshell *shell)
{
	printf("NÃO FOI FEITO ESSE BUILTIN %s\n", cmd[0]->args[0]);
	gc_clear (shell->collector);
	exit (0);
}
