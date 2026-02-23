/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 21:16:11 by lbento            #+#    #+#             */
/*   Updated: 2026/02/22 21:35:29 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	fill_last_expandable(t_token **tokens, int expandable)
{
	t_token	*last;

	last = *tokens;
	while (last->next)
		last = last->next;
	last->expandable = expandable;
}
