/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:10:52 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/17 18:28:39 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

void	execute_all(t_shell *shell)
{
	t_cmd_list_node	*node;

	shell->new_enw = create_new_env(shell);
	if (shell->new_enw == NULL)
		my_exit2(1);
	shell->status = STATE_EXECUTING_COMMAND;
	if (shell->pipe_count == 0)
	{
		node = shell->all_cmd->head;
		while (node != NULL)
		{
			if (node->op_code == RMNODE && node->cmd[0] != NULL)
				single_cmd(shell, node);
			node = node->next;
		}
	}
	else
		execute_pipes(shell);
}
