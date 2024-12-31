/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:15 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 11:28:49 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

t_hidden_item_lst	*init_hide_item_list(void)
{
	t_hidden_item_lst	*lst;

	lst = (t_hidden_item_lst *)malloc(sizeof(t_hidden_item_lst));
	if (lst == NULL)
		exit(0);
	lst->head = NULL;
	return (lst);
}

t_hidden_item_lst_node	*create_hide_list_node(char *data)
{
	t_hidden_item_lst_node	*node;

	node = (t_hidden_item_lst_node *)malloc(sizeof(t_hidden_item_lst_node));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

void	add_hide_list(t_hidden_item_lst *lst, t_hidden_item_lst_node *new_node)
{
	t_hidden_item_lst_node	*node;

	if (lst->head == NULL)
		lst->head = new_node;
	else
	{
		node = lst->head;
		while (node->next != NULL)
			node = node->next;
		node->next = new_node;
	}
}

void	pop_first_node(t_hidden_item_lst *lst)
{
	t_hidden_item_lst_node	*node;

	node = lst->head;
	lst->head = node->next;
	free(node->data);
	node->next = NULL;
	free(node);
}

void	free_hidden_item_lst(t_hidden_item_lst *lst, int code)
{
	t_hidden_item_lst_node	*node;
	t_hidden_item_lst_node	*next_node;

	node = lst->head;
	while (node != NULL)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	if (code == 1)
		free(lst);
	else
		lst->head = NULL;
}
