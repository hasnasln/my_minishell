/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:40 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/17 14:40:40 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

int	str_replace(char **src, char *old, char *new)
{
	char	*result;
	int		started;
	int		end;

	started = find(*src, old, 0);
	if (started == -1)
		return (-1);
	end = started + ft_strlen(old) - 1;
	result = ft_change(new, *src, started, end);
	if (result == NULL)
		return (-2);
	free(*src);
	*src = result;
	return (started);
}
