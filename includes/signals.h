/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:20:11 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 12:45:07 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

typedef enum s_signals
{
	INIT,
	HEREDOC,
	HEREDOC_END,
	EXIT_CMD,
	IN_CMD,
	CTRL_C
}			t_status;

void	sig_init(void);

#endif