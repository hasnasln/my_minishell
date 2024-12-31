/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:22:04 by haslan            #+#    #+#             */
/*   Updated: 2023/10/22 15:00:57 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	number_size(int s)
{
	int	len;

	len = 0;
	if (s == 0)
		return (2);
	if (s <= 0)
		len++;
	while (s != 0)
	{
		s = s / 10;
		len++;
	}
	return (len + 1);
}

static unsigned int	step(unsigned int number)
{
	unsigned int	s;

	if (number >= 1000000000)
		return (1000000000);
	s = 1;
	while (s * 10 <= number)
		s = s * 10;
	return (s);
}

static unsigned int	r_number(int a)
{
	unsigned int	x;

	if (a < 0)
		x = a * -1;
	if (a >= 0)
		x = a;
	return (x);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	nstep;
	int				i;

	i = 0;
	str = (char *)malloc(sizeof(char) * number_size(n));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	nb = r_number(n);
	nstep = step(nb);
	while (nstep > 0)
	{
		str[i++] = (nb / nstep) + '0';
		nb = nb - ((nb / nstep) * nstep);
		nstep = nstep / 10;
	}
	str[i] = '\0';
	return (str);
}
