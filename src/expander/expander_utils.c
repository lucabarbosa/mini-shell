/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:34 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/22 19:02:57 by lbento           ###   ########.fr       */
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

int	cond(char *arg, int i)
{
	return (arg[i] == '$' && arg[i + 1] != '$'
		&& arg[i + 1] != '?' && arg[i + 1]
		&& envchr(arg[i + 1]));
}

char	*concat_cmd( char **res, char *arg, int i, t_gc **gc)
{
	char	tmp[2];

	tmp[1] = '\0';
	tmp[0] = arg[i];
	*res = ft_strjoin(*res, tmp, gc);
	return (*res);
}
