/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:15:20 by haslan            #+#    #+#             */
/*   Updated: 2023/10/22 15:02:03 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*s;

	s = (unsigned char *)src;
	p = (unsigned char *)dest;
	if (s == NULL && p == NULL)
		return (dest);
	while (n)
	{
		*p = *s;
		p++;
		s++;
		n--;
	}
	return (dest);
}
