/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_past.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:34 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 17:46:41 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

int	count_need_charptr(t_shell *shell, int counter)
{
	t_cmd_list_node	*node;
	int				j;

	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == -1)
		{
			j = -1;
			while (node->cmd != NULL && node->cmd[++j] != NULL)
				counter++;
			if (counter == 0 && node->cmd != NULL)
				counter++;
		}
		else if (node->op_code == PIPE && counter == 0)
		{
			node = node->next;
			continue ;
		}
		else if (node->op_code == PIPE && counter != 0)
			break ;
		node = node->next;
	}
	return (counter);
}

void	copy_node_commands(t_cmd_list_node *node, char ***new_cmd,
	int *j, int *counter)
{
	int	i;

	i = -1;
	while (node->cmd[++i] != NULL)
	{
		(*new_cmd)[*j] = node->cmd[i];
		(*j)++;
		node->cmd[i] = NULL;
		(*counter)++;
	}
	if (node->cmd != NULL && *counter == 0)
		(*counter)++;
	node->op_code = FNODE;
}

void	gather_commands(t_shell *shell, int i, char ***new_cmd)
{
	t_cmd_list_node	*node;
	int				counter;
	int				j;

	(void)i;
	node = shell->all_cmd->head;
	counter = 0;
	j = 0;
	while (node != NULL)
	{
		if (node->op_code == -1)
			copy_node_commands(node, new_cmd, &j, &counter);
		else if (node->op_code == PIPE && counter == 0)
		{
			node = node->next;
			continue ;
		}
		else if (node->op_code == PIPE && counter != 0)
		{
			(*new_cmd)[j] = NULL;
			break ;
		}
		node = node->next;
	}
}

void	assign_commands(t_shell *shell, char **new_cmd)
{
	t_cmd_list_node	*node;

	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == FNODE)
		{
			if (node->cmd)
				free(node->cmd);
			node->cmd = new_cmd;
			new_cmd = NULL;
			node->op_code = MNODE;
			break ;
		}
		node = node->next;
	}
	node = shell->all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == FNODE)
			node->op_code = WNODE;
		node = node->next;
	}
}

void	the_past(t_shell *shell)
{
	int		counter;
	char	**new_cmd;

	while (1)
	{
		counter = count_need_charptr(shell, 0);
		if (counter == 0)
			break ;
		new_cmd = (char **)ft_calloc(sizeof(char *), (counter + 1));
		if (new_cmd == NULL)
			my_exit2(1);
		gather_commands(shell, 0, &new_cmd);
		assign_commands(shell, new_cmd);
	}
}
