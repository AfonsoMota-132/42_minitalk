/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:06:46 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/16 14:07:23 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libs/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define PAUSE 100

typedef struct s_data
{
	int		size;
	int		bits;
	int		bytes;
	int		received;
	char	*msg;
}	t_data;
#endif
