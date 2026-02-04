/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaratang <iaratang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:31:07 by lbento            #+#    #+#             */
/*   Updated: 2026/02/03 11:13:24 by iaratang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int	command_cd(char **args, t_mshell *shell);
static char *get_target_path(char **args, t_mshell *shell);

int	command_cd(char **args, t_mshell *shell)
{
	int   print;
   char  *target;
   int   old_pwd[4096];

   print = 0;
   if (args[2] && args[2])
   {
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);  
   }
   if (getcwd(old_pwd, 4096) == NULL)
      old_pwd[0] = '\0';
   target = get_target_path(args, shell);
   if (!target)
      return (1);
   if (chadir(args[0]) == -1)
      return (1);
   return (0);
}

static char *get_target_path(char **args, t_mshell *shell)
{
   char  *target;

   if (args[1][0] == '~' || !args[1])
   {
      target = get_env_value("HOME", shell->envp);
      if (!target || !target [0])
      {
         ft_putendl_fd("minishell: cd: HOME not set", 2);
         return (NULL);
      }
   }
   else if (args[1][0] == '-')
   {
      target = get_env_value("OLDPWD", shell->envp);
      if (!target || !target [0])
      {
         ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
         return (NULL);
      }
   }
   else
      target = args[1];
   return (target);
}