/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_settings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:00:51 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:34:27 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../../my_include/shell.h"

t_cmd_list_node	*get_node(t_cmd_list *all_cmd, int *count)
{
	t_cmd_list_node	*node;
	int				i;

	i = 0;
	node = all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == MNODE)
		{
			*count = i;
			return (node);
		}
		else if (node->op_code == PIPE)
			i++;
		node = node->next;
	}
	return (NULL);
}

static int	update_output_fd(t_cmd_list_node *node,
	t_cmd_list_node *node_to_update, int opcode)
{
	int	fd;

	fd = 0;
	if (opcode == RD)
		fd = open(node->cmd[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (opcode == RDD)
		fd = open(node->cmd[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		get_shell()->exit_status = 1;
		return (1);
	}
	else
	{
		get_shell()->exit_status = 0;
		if (node_to_update->fd_out == -1 || node_to_update->fd_out == 1)
			node_to_update->fd_out = fd;
		else
		{
			close(node_to_update->fd_out);
			node_to_update->fd_out = fd;
		}
	}
	return (0);
}

static int	update_input_fd(t_cmd_list_node *node,
	t_cmd_list_node *node_to_update)
{
	int	fd;

	fd = open(node->cmd[0], O_RDONLY);
	if (fd == -1)
	{
		get_shell()->exit_status = 1;
		perror("open");
		return (1);
	}
	else
	{
		get_shell()->exit_status = 0;
		if (node_to_update->fd_in == -1 || node_to_update->fd_in == 0)
			node_to_update->fd_in = fd;
		else
		{
			close(node_to_update->fd_in);
			node_to_update->fd_in = fd;
		}
	}
	return (0);
}

int	update_fd(t_cmd_list_node *node, t_cmd_list_node *node_to_update)
{
	if (node->prev->op_code == RD && update_output_fd(node, node_to_update, RD))
		return (1);
	else if (node->prev->op_code == RDD
		&& update_output_fd(node, node_to_update, RDD))
		return (1);
	else if (node->prev->op_code == RI && update_input_fd(node, node_to_update))
		return (1);
	else if (node->prev->op_code == ERII)
	{
		if (node_to_update->fd_in == -1 || node_to_update->fd_in == 0)
			node_to_update->fd_in = node->fd_in;
		else
		{
			close(node_to_update->fd_in);
			node_to_update->fd_in = node->fd_in;
		}
	}
	return (0);
}

int	redirection_settings(t_shell *shell)
{
	t_cmd_list_node	*node_to_update;
	int				count;

	count = 0;
	while (1)
	{
		node_to_update = NULL;
		node_to_update = get_node(shell->all_cmd, &count);
		if (node_to_update == NULL)
			break ;
		if (update_cmd_io(shell, node_to_update, &count))
			return (1);
		node_to_update->op_code = RMNODE;
	}
	return (0);
}
