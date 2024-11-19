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

void	ft_free(char **temp)
{
	if (temp && *temp)
	{
		free(*temp);
		*temp = NULL;
	}
}

void	fill_null(int bytes[8])
{
	int	bits;

	bits = -1;
	while (++bits < 8)
		bytes[bits] = 0;
}

/*int	size_handler(int signum)*/
/*{*/
/*	static int	bits;*/
/*	static int	bytes[32];*/
/**/
/*	if (!bits)*/
/*		bits = 0;*/
/*	if (signum == SIGUSR1)*/
/*		return (0);	*/
/*	else if (signum == SIGUSR2)*/
/*		return (1);*/
/*	return ();*/
/*}*/

void	put_char(t_data data)
{
	static	char	*str;

	if (!str)
		str = "";
	/*if (data.bytes == 0)*/
	/*{*/
	/*	ft_printf("\nend\n");*/
	/*	str = ft_chrjoin(str, char_in);*/
	/*}*/
	if (data.bytes)
	{
		ft_printf("%c", data.bytes);
	}
}

void	signal_handler(int signum)
{
	static t_data	data;

	if (!data.bits)
	{
		data.bytes = 0;
		data.bits = 0;
	}
	if (signum == SIGUSR1)
		data.bytes |= 1 << (7 - data.bits);
	else if (signum == SIGUSR2)
		data.bytes &= ~(1 << (7 - data.bits));
	++data.bits;
	/*if (data.bits == 32 && !data.received)*/
	/*{*/
	/*	ft_printf("size: %i\nbits: %i\n", data.bytes, data.bits);*/
	/*	data.received = 1;*/
	/*	data.bytes = 0;*/
	/*	data.bits = 0;*/
	/*}*/
	if (data.bits == 8 && data.received == 1)
	{
		put_char(data);
		data.bits = 0;
		data.bytes = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal;

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
