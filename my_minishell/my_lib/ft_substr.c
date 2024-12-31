/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:23:56 by haslan            #+#    #+#             */
/*   Updated: 2023/10/22 15:32:00 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*cpy(char *str, int first, int last)
{
	char	*sr;
	int		i;

	i = 0;
	sr = (char *)malloc((last + 1) * sizeof(char));
	if (!sr)
		return (NULL);
	while (i < last)
	{
		sr[i] = str[first + i];
		i++;
	}
	sr[i] = '\0';
	return (sr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (NULL);
		*substr = '\0';
	}
	else
	{
		if (start + len > ft_strlen(s))
			len = (ft_strlen(s) - start);
		substr = cpy((char *)s, start, len);
		if (!substr)
			return (NULL);
	}
	return (substr);
}
