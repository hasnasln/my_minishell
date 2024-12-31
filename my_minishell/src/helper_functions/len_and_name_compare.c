/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_and_name_compare.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:38 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 11:20:18 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

int	len_and_name_compare(char *str, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == ft_strlen(str2))
	{
		while (str[i])
		{
			if (str[i] != str2[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

static int	ftt_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	check_builtin_possibility(char *str, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == ft_strlen(str2))
	{
		while (str[i])
		{
			if (ftt_tolower(str[i]) != ftt_tolower(str2[i]))
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}
