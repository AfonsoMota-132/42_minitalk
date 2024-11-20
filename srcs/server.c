/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:56:59 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/16 13:57:05 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"
#include <signal.h>

void	calloc_size(t_data *data)
{
	if (data->bits == 32 && !data->received)
	{
		data->msg = malloc((data->bytes + 1) * sizeof(char));
		if (!data->msg)
		{
			ft_printf("Malloc failed\n");
			exit (0);
		}
		data->msg[data->bytes] = '\0';
		data->received = 1;
		data->bits = 0;
	}
}

void	put_char(t_data *data)
{
	static char		*str;
	static int		i;

	if (!str)
		str = "";
	if (!data->bytes)
	{
		ft_printf("%s\n", data->msg);
		data->received = 0;
		free(data->msg);
		i = 0;
		data->msg = NULL;
	}
	else
	{
		data->msg[i] = data->bytes;
		i++;
	}
}

void	signal_handler(int signum)
{
	static t_data	data;

	if (!data.bits)
		data.bytes = 0;
	if (signum == SIGUSR1 && data.received)
		data.bytes |= 1 << (7 - data.bits);
	else if (signum == SIGUSR2 && data.received)
		data.bytes &= ~(1 << (7 - data.bits));
	else if (signum == SIGUSR1 && !data.received)
		data.bytes |= 1 << (31 - data.bits);
	else if (signum == SIGUSR2 && !data.received)
		data.bytes &= ~(1 << (31 - data.bits));
	++data.bits;
	calloc_size(&data);
	if (data.bits == 8 && data.received == 1)
	{
		put_char(&data);
		data.bits = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal;

	sigemptyset(&signal.sa_mask);
	signal.sa_handler = &signal_handler;
	signal.sa_flags = 0;
	pid = getpid();
	if (pid == -1)
	{
		ft_printf("Invalid PID\n");
		exit (1);
	}
	ft_printf("Server PID: %i\n", pid);
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
		pause();
}
