/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:22 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:30:54 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_2d(char **arr)
{
	int	i;

	i = -1;
	while (arr != NULL && arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_2d_int(int **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(arr[i]);
	free(arr);
}
