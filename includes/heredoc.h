/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:07:01 by lbento            #+#    #+#             */
/*   Updated: 2026/02/05 18:16:51 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "executor.h"
# include "builtin.h"

typedef struct s_cmd		t_cmd;
typedef struct s_mshell		t_mshell;
typedef struct s_envlist	t_envlist;

int		handle_heredocs(t_cmd *cmd, int i, t_mshell *shell);
void	cleanup_heredoc(t_cmd *cmd);

#endif