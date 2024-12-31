/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:56:10 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 10:57:39 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

t_env_list	*creat_envlst(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (env_list == NULL)
		return (NULL);
	env_list->head = NULL;
	env_list->tail = NULL;
	env_list->list_size = 0;
	return (env_list);
}

t_env_var	*create_envlst_node(char *name, char *data)
{
	t_env_var	*node;

	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->name = name;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	add_envlst_node(t_env_list *env_list, t_env_var *node)
{
	if (node == NULL)
		return (0);
	if (env_list->head == NULL)
	{
		env_list->head = node;
		env_list->tail = node;
	}
	else
	{
		env_list->tail->next = node;
		node->prev = env_list->tail;
		env_list->tail = node;
	}
	env_list->list_size++;
	return (1);
}

t_env_var	*find_envlst_node(t_env_list *env_list, char *name)
{
	t_env_var	*moving;

	moving = env_list->head;
	while (moving)
	{
		if (len_and_name_compare(name, moving->name))
			return (moving);
		moving = moving->next;
	}
	return (NULL);
}

void	free_envlst(t_env_list *env_list)
{
	t_env_var	*moving;
	t_env_var	*tmp;

	moving = env_list->head;
	while (moving)
	{
		tmp = moving;
		moving = moving->next;
		free(tmp->name);
		free(tmp->data);
		free(tmp);
	}
	free(env_list);
}
