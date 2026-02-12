/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:07:01 by lbento            #+#    #+#             */
/*   Updated: 2026/02/12 03:15:52 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "executor.h"
# include "builtin.h"

typedef struct s_redir		t_redir;
typedef struct s_cmd	   	t_cmd;
typedef struct s_mshell		t_mshell;
typedef struct s_envlist	t_envlist;

int		handle_heredocs(t_cmd *cmd, t_mshell *shell);
void	cleanup_heredoc(t_cmd *cmd);
char	*parse_delim(char *delim, int *expand, t_mshell *shell);
int		create_temp_file(t_redir *current, int index, t_mshell *shell);
int		is_delimiter(char *line, char *delimiter);
void	fill_line(char *line, int fd, int expand, t_mshell *shell);

#endif