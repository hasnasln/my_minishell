/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recent_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:29 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 14:03:56 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

int	prev_is_one_of_my_rd(t_cmd_list_node *node)
{
	if (node->prev != NULL)
	{
		if (node->prev->op_code == RD || node->prev->op_code == RDD
			|| node->prev->op_code == RI || node->prev->op_code == RII)
			return (1);
	}
	return (0);
}

void	update_op_codes(t_shell *shell)
{
	t_cmd_list_node	*node;

	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if (node->prev != NULL && prev_is_one_of_my_rd(node))
			node->op_code = FNAME;
		node = node->next;
	}
}

void	split_and_insert_nodes(t_shell *shell, t_cmd_list_node *node,
	t_cmd_list_node *new)
{
	char	**part1;
	char	**part2;

	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if ((node->op_code == FNAME) && node->cmd[1] != NULL)
		{
			brak_node(node, &part1, &part2, 1);
			free(node->cmd);
			node->cmd = part1;
			new = create_cmd_node(part2, -1, -1);
			if (new == NULL)
				my_exit2(1);
			if (node->next != NULL)
			{
				new->next = node->next;
				node->next->prev = new;
			}
			node->next = new;
			new->prev = node;
		}
		node = node->next;
	}
}

void	recent_settings(t_shell *shell)
{
	t_cmd_list_node	*node;
	t_cmd_list_node	*new;

	node = NULL;
	new = NULL;
	update_op_codes(shell);
	split_and_insert_nodes(shell, node, new);
	the_past(shell);
}
