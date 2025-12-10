/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:49:55 by lbento            #+#    #+#             */
/*   Updated: 2025/12/10 16:09:49 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1048576
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*read_line(int fd, char *remaining, char *buffer);
char	*save_file(char *line);

#endif