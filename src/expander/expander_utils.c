/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:34 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/04 20:15:40 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	envchr(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	chktp(t_token token)
{
	return (token.type == TOKEN_DQUOTE || token.type == TOKEN_WORD);
}

void	init_var(int *i, char **res, char *tmp, t_gc **gc)
{
	*i = 0;
	*res = ft_strdup("", gc);
	tmp[1] = '\0';
}
