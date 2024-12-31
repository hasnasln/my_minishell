/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:27 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:31:04 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

char	*ft_change(char *new, char *old, int start, int end)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(old) - (end - start + 1) + ft_strlen(new) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	j = -1;
	i = 0;
	while (++j < start)
		result[i++] = old[j];
	j = -1;
	while (new[++j] != '\0')
		result[i++] = new[j];
	j = end;
	while (old[++j] != '\0')
		result[i++] = old[j];
	result[i] = '\0';
	return (result);
}
