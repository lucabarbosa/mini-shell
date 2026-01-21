/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:38:34 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/21 21:01:18 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../includes/minishell.h"
#include "../includes/executor.h"

//parser
t_cmd  *parser(t_token *tokens, t_gc **collector);
t_cmd   *parse_command(t_token **current, t_gc **collector);
t_cmd    *init_cmd(t_gc **collector);
int handle_redirection(t_cmd *cmd, t_token **current, t_gc  **collector);
void    add_argument(t_cmd *cmd, char *arg, t_gc **collector);
void    add_command_to_list(t_cmd **head, t_cmd *new_cmd);

//parser_utils
int check_redirection_token(t_token_type type);
int check_argument_token(t_token_type type);
void print_commands(t_cmd *commands);

#endif
