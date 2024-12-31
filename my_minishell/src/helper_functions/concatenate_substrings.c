/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_substrings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:17 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 11:14:18 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

static	int	split_result_total_len(char **str)
{
	int	total_len;
	int	len;
	int	i;

	i = -1;
	total_len = 0;
	while (str[++i])
	{
		len = -1;
		while (str[i][++len])
			;
		total_len += len;
	}
	total_len += (i - 1);
	return (total_len);
}

char	*concatenate_substrings(char **str, char c)
{
	char	*r_str;
	int		i;
	int		j;
	int		k;

	r_str = (char *)malloc(sizeof(char) * (split_result_total_len(str) + 1));
	if (!r_str)
		return (NULL);
	i = -1;
	k = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			r_str[++k] = str[i][j];
		free_and_null((void **)&str[i]);
		if (str[i + 1])
			r_str[++k] = c;
	}
	r_str[++k] = '\0';
	return (r_str);
}
