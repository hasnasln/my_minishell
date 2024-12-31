/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:29 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/17 14:40:37 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	find(char *src, char *wanted, int start)
{
	int	i;
	int	j;

	i = start;
	if (src == NULL || wanted == NULL)
		return (-1);
	while (src[i])
	{
		j = 0;
		while (src[i + j] == wanted[j] && wanted[j] != '\0')
			j++;
		if (wanted[0] == '$' && (src[i + 1] == '\0'
				|| src[i + 1] == ' ' || src[i + 1] == '$'))
		{
			i++;
			continue ;
		}
		if (wanted[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
