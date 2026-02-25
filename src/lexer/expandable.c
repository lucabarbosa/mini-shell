/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 21:16:11 by lbento            #+#    #+#             */
/*   Updated: 2026/02/25 00:12:14 by lbento           ###   ########.fr       */
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

int	is_word_start(char c)
{
	return (c != ' ' && !is_operator(c) && c != '\'' && c != '"');
}
