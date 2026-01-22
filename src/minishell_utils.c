/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:07 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 18:44:20 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int num);

void	print_error(int num)
{
	if (num == 0)
		perror("minishell: fork");
	if (num == 1)
		perror("minishell: dup2");
	exit (1);
}
