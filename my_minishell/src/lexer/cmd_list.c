/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:21:59 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:28:02 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	add_node_cmdlist(t_cmd_list *cmdlst, t_cmd_list_node *node)
{
	if (node == NULL)
		my_exit2(1);
	if (cmdlst->cmd_size == 0)
	{
		cmdlst->head = node;
		cmdlst->tail = node;
	}
	else
	{
		cmdlst->tail->next = node;
		node->prev = cmdlst->tail;
		cmdlst->tail = node;
	}
	cmdlst->cmd_size ++;
}

t_cmd_list_node	*create_cmd_node(char **cmd, int cmd_no, int fd_out)
{
	t_cmd_list_node	*node;

	node = (t_cmd_list_node *)malloc(sizeof(t_cmd_list_node));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->operator = NULL;
	node->op_code = -1;
	node->fd_in = cmd_no;
	node->fd_out = fd_out;
	node->old_fd_in = -1;
	node->old_fd_out = -1;
	node->cmd = cmd;
	return (node);
}

t_cmd_list_node	*crate_opreator(char *cmd, int op_code)
{
	t_cmd_list_node	*node;

	node = (t_cmd_list_node *)malloc(sizeof(t_cmd_list_node));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->cmd = NULL;
	node->operator = cmd;
	node->op_code = op_code;
	node->fd_in = -1;
	node->fd_out = -1;
	node->old_fd_in = -1;
	node->old_fd_out = -1;
	return (node);
}

t_cmd_list	*init_cmd_list(void)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (list == NULL)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->cmd_size = 0;
	return (list);
}

void	free_cmd_list(t_cmd_list *list)
{
	t_cmd_list_node	*node;
	t_cmd_list_node	*tmp;

	node = list->head;
	while (node)
	{
		if (node->cmd)
			free_2d(node->cmd);
		if (node->operator)
			free(node->operator);
		tmp = node->next;
		node->next = NULL;
		node->prev = NULL;
		free(node);
		node = tmp;
	}
	free(list);
}
