/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:06:10 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/16 14:06:24 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
void	signal_sender(char *str, pid_t pid)
{
	int		bit;
	char	octet;

	while (*str != '\0')
	{
		bit = 8;
		octet = *str;
		while (bit--)
		{
			if (octet % 2 == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			octet /= 2;
			usleep(100);
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	pid_t pid;

	pid = atoi(av[1]);
	signal_sender(av[2], pid);	
}
