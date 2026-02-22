/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:07:16 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/22 19:15:05 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_cmd(char *arg, t_gc **gc, t_mshell *shell);
char		*srchcmd(char *cmd, t_envlist *env);
int			envchr(char c);
static void	check_prev_next(t_token **tokens);

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

void	remove_empty_expanded(t_token **tokens)
{
	while (*tokens && (*tokens)->expandable && (*tokens)->value
		&& (*tokens)->value[0] == '\0'
		&& (*tokens)->type != TOKEN_END)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			(*tokens)->prev = NULL;
	}
	if (!*tokens)
		return ;
	check_prev_next(tokens);
}

static void	check_prev_next(t_token **tokens)
{
	t_token	*cr;
	t_token	*next;

	cr = *tokens;
	while (cr)
	{
		next = cr->next;
		if (cr->expandable && cr->value && cr->value[0] == '\0'
			&& cr->type != TOKEN_END)
		{
			if (cr->prev)
				cr->prev->next = cr->next;
			if (cr->next)
				cr->next->prev = cr->prev;
		}
		cr = next;
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
