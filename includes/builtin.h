/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:30:53 by lbento            #+#    #+#             */
/*   Updated: 2026/01/22 00:20:01 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_cmd t_cmd;
typedef struct s_mshell t_mshell;

int		is_builtin(char *cmd);
void	exec_builtin(t_cmd **cmd, t_mshell *shell);

#endif