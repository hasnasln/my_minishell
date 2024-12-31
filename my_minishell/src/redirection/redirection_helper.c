/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:00:37 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 12:02:00 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

int	update_cmd_io(t_shell *shell, t_cmd_list_node *node_to_update, int *count)
{
	t_cmd_list_node	*node;

	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == FNAME)
		{
			if (update_fd(node, node_to_update))
				return (1);
			node->op_code = OFNAME;
		}
		else if (node->op_code == PIPE && *count != 0)
		{
			(*count)--;
			node = node->next;
		}
		else if (node->op_code == PIPE && *count == 0)
			break ;
		node = node->next;
	}
	return (0);
}
