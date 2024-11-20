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
			return ;
		data->size = data->bytes;
		data->msg[data->bytes] = '\0';
		data->received = 1;
		data->bits = 0;
	}
}

void	put_char(t_data *data, siginfo_t *info)
{
	static char		*str;
	static int		i;

	if (!str)
		str = "";
	if (!data->bytes)
	{
		ft_printf("before\n");
		ft_printf("%s\n", data->msg);
		ft_printf("after\n");
		write(1, "\n", 1);
		data->received = 0;
		free(data->msg);
		i = 0;
		kill(info->si_pid, SIGUSR1);
		data->msg = NULL;
	}
	else
	{
		data->msg[i] = data->bytes;
		i++;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *content)
{
	static t_data	data;

	(void) content;
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
		put_char(&data, info);
		data.bits = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal;

	sigemptyset(&signal.sa_mask);
	signal.sa_sigaction = &signal_handler;
	signal.sa_flags = SA_SIGINFO;
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
