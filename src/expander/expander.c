/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:16 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/03 13:49:09 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expd(t_token *tokens, t_gc **gc, char **env)
{
	int		i;
	char	*cmd;
	
	i = 0;
	while (tokens != NULL)
	{
		if (chktp(*tokens))
			if (chkx(tokens->value))
			{	
				cmd = chkcmd(tokens->value, gc, env);
				tokens->type = TOKEN_ENV_VAR;
				tokens->value = cmd;
			}
		tokens = tokens->next;
	}
	
}

char	*chkcmd(char *arg, t_gc **gc, char **env)
{
	int		j;
	int		i;
	char	*env_v;
	char 	*res;
	char	tmp[2];

	init_var(&i, &res, tmp, gc);
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			j = ++i;
			while (envchr(arg[i]))
				i++;
			env_v = srchcmd(ft_substr(arg, j, i - j, gc), env);
			if (env_v)
				res = ft_strjoin(res, env_v, gc);
		}
		else
		{
			tmp[0] = arg[i];
			res = ft_strjoin(res, tmp, gc);
			i++;
		}
	}
	return (res);
}

char	*srchcmd(char *cmd, char **env)
{
	char *env_v;

	env_v = get_env_value(cmd, env);
	if (env_v)
		return (env_v);
	else 
		return (NULL);
}

int	chkx(char *arg)
{
	int	i;
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
