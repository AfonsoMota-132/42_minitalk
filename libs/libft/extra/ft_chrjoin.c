/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:07:46 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/17 11:07:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_chrjoin(char const *str, char const chr)
{
	size_t	size;
	size_t	i;
	char	*dstr;

	i = -1;
	if (!chr)
		return (NULL);
	if (!str)
		size = 1;
	else
		size = ft_strlen(str) + 1;
	dstr = (char *) malloc(sizeof(char) * (size + 1));
	if (dstr == NULL)
		return (NULL);
	if (str != NULL)
	{
		while (str[++i] != '\0')
			dstr[i] = str[i];
	}
	dstr[i] = chr;
	i++;
	dstr[i] = '\0';
	return (dstr);
}
