/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:21:56 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 17:46:05 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	brak_node(t_cmd_list_node *node, char ***p1_address,
		char ***p2_address, int index)
{
	char			**part1;
	char			**part2;
	int				i;

	part1 = (char **)malloc(sizeof(char *) * (index + 1));
	if (part1 == NULL)
		my_exit2(1);
	i = 0;
	while (node->cmd[i] != NULL)
		i++;
	part2 = (char **)malloc(sizeof(char *) * (i - index + 1));
	if (part2 == NULL)
		my_exit2(1);
	i = -1;
	while (++i < index)
		part1[i] = node->cmd[i];
	part1[i] = NULL;
	i = -1;
	while (node->cmd[index] != NULL)
		part2[++i] = node->cmd[index++];
	part2[++i] = NULL;
	*p1_address = part1;
	*p2_address = part2;
}
