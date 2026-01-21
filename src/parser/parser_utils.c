/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:33:21 by iaratang          #+#    #+#             */
/*   Updated: 2026/01/21 20:48:41 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_redirection_token(t_token_type type)
{
    return (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);  
}

int check_argument_token(t_token_type type)
{
    return (type == TOKEN_WORD || type == TOKEN_DQUOTE || type == TOKEN_SQUOTE || type == TOKEN_ENV_VAR);
}

void print_commands(t_cmd *commands)
{
    t_cmd *current;
    int cmd_num;
    int i;
    
    current = commands;
    cmd_num = 1;
    
    printf("\n==========COMMANDS==========\n");
    while (current)
    {
        printf("Command #%d:\n", cmd_num);
        
        printf("  Args: ");
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                printf("[%s] ", current->args[i]);
                i++;
            }
        }
        else
            printf("(none)");
        printf("\n");
        
        printf("  Input: %s\n", current->input ? current->input : "(none)");
        printf("  Output: %s\n", current->output ? current->output : "(none)");
        printf("  Append: %s\n", current->append ? "yes" : "no");
        printf("----------------------------\n");
        
        current = current->next;
        cmd_num++;
    }
    printf("============================\n\n");
}
