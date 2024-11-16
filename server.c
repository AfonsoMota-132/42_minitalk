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

#include "minitalk.h"
#include <signal.h>
#include <unistd.h>

void	put_char(int *c)
{
	int		i;
	unsigned char	char_in;

	i = 7;
	char_in = 0;
	while (i >= 0)
		char_in = char_in * 2 + c[i--];
	write(1, &char_in, 1);
}
void	signal_handler(int signum)
{
	static int	bits;
	static int	bytes[8];

	if (!bits)
		bits = 0;
	if (signum == SIGUSR1)
		bytes[bits] = 0; 
	else if (signum == SIGUSR2)
		bytes[bits] = 1;
	bits++;
	if (bits == 8)
	{
		put_char(bytes);
		bits = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	struct sigaction signal;

	signal.sa_handler = &signal_handler;
	pid = getpid();
	printf("%i\n", pid);
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
		pause();

}
