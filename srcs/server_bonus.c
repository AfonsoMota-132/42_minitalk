/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:11:34 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/17 18:13:39 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

void	put_char(int *c, siginfo_t *info)
{
	int				i;
	unsigned char	char_in;

	i = 7;
	char_in = 0;
	while (i >= 0)
		char_in = char_in * 2 + c[i--];
	if (!char_in)
	{
		ft_printf("END OF MESSAGE\n");
		kill(info->si_pid, SIGUSR1);
	}
	else
		ft_printf("%c", char_in);
}
void	fill_null(int bytes[8])
{
	int	bits;

	bits = -1;
	while (++bits < 8)
		bytes[bits] = 0;
}

void	signal_handler(int signum, siginfo_t *info, void *content)
{
	static int	bits;
	static int	bytes[8];

	(void) content;
	if (!bits)
		bits = 0;
	if (signum == SIGUSR1)
		bytes[bits] = 0; 
	else if (signum == SIGUSR2)
		bytes[bits] = 1;
	bits++;
	if (bits == 8)
	{
		put_char(bytes, info);
		bits = 0;
		fill_null(bytes);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal;

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
