/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:23:35 by haslan            #+#    #+#             */
/*   Updated: 2023/10/22 15:05:11 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strj;
	char	*strj2;

	strj = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (strj == NULL)
		return (0);
	strj2 = strj;
	while (*s1)
	{
		*strj = *s1;
		strj++;
		s1++;
	}
	while (*s2)
	{
		*strj = *s2;
		strj++;
		s2++;
	}
	*strj = '\0';
	return (strj2);
}
