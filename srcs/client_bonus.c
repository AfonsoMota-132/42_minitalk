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
		bit = sizeof(char) * 8;
		octet = *str;
		while (bit--)
		{
			if (octet >> bit & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(PAUSE);
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
		kill(pid, SIGUSR2);
		usleep(PAUSE);
	}
}

void	size_sender(int size, pid_t pid)
{
	int	bits;

	bits = 31;
	while (bits >= 0)
	{
		if (size >> bits & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bits--;
		usleep(PAUSE);
	}
}

void	confirm(int signum)
{
	(void) signum;
	ft_printf("Message Received\n");
	exit (0);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		len;

	if (ac == 3)
	{
		signal(SIGUSR1, confirm);
		pid = ft_atoi(av[1]);
		if (kill(pid, 0))
		{
			ft_printf("Invalide Pid\n");
			exit (1);
		}
		len = ft_strlen(av[2]);
		size_sender(len, pid);
		signal_sender(av[2], pid);
		end_signal(pid);
		while (1)
			pause ();
	}
}
