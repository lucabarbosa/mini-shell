/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:02:31 by lbento            #+#    #+#             */
/*   Updated: 2026/02/03 13:55:34 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "executor.h"
# include "builtin.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_mshell
{
	t_gc	*collector;
	t_gc	*envp_collect;
	char	**envp;
	int		env_size;
	int		env_capacity;
	int		last_exit;
	int		running;
}	t_mshell;

char	*get_env_value(char *name, char **envp);
int		find_env_index(char *name, char **envp);
void	remove_env_var(int index, t_mshell *shell);
void	clean_shell(t_mshell *shell);
void	print_error(int num, t_mshell *shell);

void	sigint_handler(int sig);

#endif
