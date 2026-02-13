/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:38:34 by iaratang          #+#    #+#             */
/*   Updated: 2026/02/13 12:44:51 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "executor.h"
# include "builtin.h"

t_cmd	*parser(t_token *tokens, t_gc **collector);
t_cmd	*parse_command(t_token **current, t_gc **collector);
t_cmd	*init_cmd(t_gc **collector);

void	add_command_to_list(t_cmd **head, t_cmd *new_cmd);
void	add_argument(t_cmd *cmd, char *arg, t_gc **collector);
void	add_redir(t_cmd *cmd, int type, char *file, t_gc **collector);
void	add_heredoc_redir(t_cmd *cmd, char *delim, int expand, t_gc **collect);
int		handle_redirection(t_cmd *cmd, t_token **current, t_gc **collector);

int		check_argument_token(t_token_type type);
int		check_redirection_token(t_token_type type);

int		handle_heredoc(t_cmd *cmd, t_token **tokens, t_gc **collector);

#endif
