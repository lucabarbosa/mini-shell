/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:02:31 by lbento            #+#    #+#             */
/*   Updated: 2026/02/22 18:27:35 by lbento           ###   ########.fr       */
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
# include "signals.h"

typedef struct s_mshell
{
	t_gc				*collector;
	t_gc				*envp_collect;
	char				**env_char;
	int					last_exit;
	int					running;
	struct s_envlist	*envp;
	int					stdin_backup;
	int					stdout_backup;
}	t_mshell;

typedef struct s_envlist
{
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

extern volatile sig_atomic_t	g_signal;

char			*get_env_value(char *name, t_envlist *envp);
void			remove_env_var(char *name, t_mshell *shell);
void			clean_shell(t_mshell *shell);
void			print_error(int num, t_mshell *shell);
void			restore_fds(char *input, t_mshell *shell);
void			set_exit(t_mshell *shell);
void			init_shell(t_mshell *shell, char **envp);
t_envlist		*init_envp(char **envp, t_gc **gc, int i);
int				input_process(char *input, t_mshell *shell);
void			shell_loop(t_mshell *shell);
void			cmd_executor(t_token *tokens, t_mshell *shell);

void			sigint_handler(int sig);
void			sigint_heredoc(int sig);
void			sig_wait(void);
void			sig_child(void);

#endif
