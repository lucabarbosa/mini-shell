/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:31:06 by lbento            #+#    #+#             */
/*   Updated: 2026/01/28 23:40:40 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int   command_pwd(void);

int   command_pwd(void)
{
   char  current_path[4096];
   
   if (getcwd(current_path, 4096) == NULL)
   {
      perror("minishell: getcwd");
      return (1);
   }
  	printf("%s\n", current_path);
	return (0);
}
