/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:16 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 11:03:05 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_cmd(char *arg, t_gc **gc, t_mshell *shell);
static char	*concat_cmd( char **res, char *arg, int i, t_gc **gc);
char		*srchcmd(char *cmd, t_envlist *env);
int			envchr(char c);

void	expand(t_token *tokens, t_gc **gc, t_mshell *shell)
{
	t_token	*cr;

	cr = tokens;
	while (cr != NULL)
	{
		if (cr->expandable)
		{
			cr->value = find_cmd(cr->value, gc, shell);
		}
		cr = cr->next;
	}
}

static char	*find_cmd(char *arg, t_gc **gc, t_mshell *shell)
{
	t_expctx	ctx;
	int			i;

	ctx.arg = arg;
	ctx.gc = gc;
	ctx.shell = shell;
	ctx.res = ft_strdup("", gc);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '$')
			handle_pid(&ctx, &i);
		else if (arg[i] == '$' && arg[i + 1] == '?')
			handle_status(&ctx, &i);
		else if (cond(arg, i))
			handle_env(&ctx, &i);
		else
		{
			ctx.res = concat_cmd(&ctx.res, arg, i, gc);
			i++;
		}
	}
	return (ctx.res);
}

char	*srchcmd(char *cmd, t_envlist *env)
{
	char	*env_v;

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
