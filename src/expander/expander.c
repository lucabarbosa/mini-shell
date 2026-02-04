/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:16 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/04 18:46:30 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *find_cmd(char *arg, t_gc **gc, char **env);
static char	*srchcmd(char *cmd, char **env);
static char	*concat_cmd( char **res, char *arg, int i, t_gc **gc);
static int	envchr(char c);

void expand(t_token *tokens, t_gc **gc, char **env)
{
	t_token	*cr;
	
	cr = tokens;
	while (cr != NULL)
	{
		if (cr->expandable)
		{
			cr->value = find_cmd(cr->value, gc, env);
		}
		cr = cr->next;
	}
}

static char *find_cmd(char *arg, t_gc **gc, char **env)
{
	int		i;
	int		j;
	char	*env_v;
	char	*res;
	
	i = 0;
	res = ft_strdup("", gc);
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
			res = concat_cmd(&res, arg, i, gc);	
			i++;
		}
	}
	return (res);
}

static char	*srchcmd(char *cmd, char **env)
{
	char *env_v;

	env_v = get_env_value(cmd, env);
	if (env_v)
		return (env_v);
	else 
		return (NULL);
}

static char	*concat_cmd( char **res, char *arg, int i, t_gc **gc)
{
	char	tmp[2];
	
	tmp[1] = '\0';
	tmp[0] = arg[i];
	*res = ft_strjoin(*res, tmp, gc);
	return (*res);
}

static int	envchr(char c)
{
	return (ft_isalnum(c) || c == '_');
}
