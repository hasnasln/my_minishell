/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:59:55 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:34:30 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	free_envnode(t_env_var *node)
{
	free(node->name);
	free(node->data);
	free(node);
}

int	remove_from_envlist(t_env_list *env_list, char *name)
{
	t_env_var	*ntd;

	ntd = find_envlst_node(env_list, name);
	if (ntd == NULL)
		return (1);
	if (ntd == env_list->head)
	{
		env_list->head = ntd->next;
		if (env_list->head != NULL)
			env_list->head->prev = NULL;
	}
	if (ntd == env_list->tail)
	{
		env_list->tail = ntd->prev;
		if (env_list->tail != NULL)
			env_list->tail->next = NULL;
	}
	if (ntd->next != NULL && ntd->prev != NULL)
	{
		ntd->prev->next = ntd->next;
		ntd->next->prev = ntd->prev;
	}
	free_envnode(ntd);
	env_list->list_size--;
	return (0);
}

static int	split_result_nume(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	make_envlst_node(t_env_list *env_list, char *namepdata)
{
	char	**r_split;
	char	*tmp;

	r_split = ft_split(namepdata, '=');
	if (r_split == NULL)
		return (1);
	if (split_result_nume(r_split) > 2)
	{
		tmp = concatenate_substrings(&r_split[1], '=');
		if (tmp == NULL)
		{
			free_2d(r_split);
			return (1);
		}
		free(r_split[1]);
		r_split[1] = tmp;
	}
	if (!add_envlst_node(env_list, create_envlst_node(r_split[0], r_split[1])))
	{
		free_2d(r_split);
		return (1);
	}
	free(r_split);
	return (0);
}

t_env_list	*charptr_to_envlst(char **env)
{
	t_env_list	*env_lnklst;
	int			i;
	int			tmp;

	i = -1;
	env_lnklst = creat_envlst();
	if (env_lnklst == NULL)
		my_exit2(1);
	while (env[++i])
	{
		tmp = make_envlst_node(env_lnklst, env[i]);
		if (tmp == 1)
			my_exit2(1);
	}
	return (env_lnklst);
}
