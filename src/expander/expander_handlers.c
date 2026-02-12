/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:51:02 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/12 18:33:46 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pid(t_expctx *ctx, int *i)
{
	ctx->res = ft_strjoin(ctx->res, ft_itoa(getpid(), ctx->gc), ctx->gc);
	*i += 2;
}

void	handle_status(t_expctx *ctx, int *i)
{
	ctx->res = ft_strjoin(ctx->res,
			ft_itoa(ctx->shell->last_exit, ctx->gc), ctx->gc);
	*i += 2;
}

void	handle_env(t_expctx *ctx, int *i)
{
	int		j;
	char	*env_v;

	j = ++(*i);
	while (envchr(ctx->arg[*i]))
		(*i)++;
	env_v = srchcmd(ft_substr(ctx->arg, j, *i - j, ctx->gc),
			ctx->shell->envp);
	if (env_v)
		ctx->res = ft_strjoin(ctx->res, env_v, ctx->gc);
}
