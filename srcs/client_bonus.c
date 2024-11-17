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

#include "../incs/minitalk.h"

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

void	end_signal(pid_t pid)
{
	int	bit;
	
		bit = 8;
		while (bit--)
		{
			kill(pid, SIGUSR1);
			usleep(100);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		ft_printf("Message Received!\n");
		exit (0);
	}
}

int	main(int ac, char **av)
{
	pid_t pid;

	if (ac == 3)
	{
		signal(SIGUSR1, &signal_handler);
		pid = ft_atoi(av[1]);
		if (kill(pid, 0))
		{
			ft_printf("Invalide Pid\n");
			exit (1);
		}
		signal_sender(av[2], pid);
		signal_sender("\n", pid);
		end_signal(pid);
		while (1)
			pause();
	}
}
