/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:22 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:33:44 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

t_env_var	**create_export_ary(t_env_list *env_list)
{
	t_env_var	**env_arry;
	t_env_var	*movig_node;
	int			i;

	i = 0;
	env_arry = (t_env_var **)malloc(sizeof(t_env_var *) * env_list->list_size);
	if (!env_arry)
		return (NULL);
	movig_node = env_list->head;
	while (movig_node)
	{
		env_arry[i] = movig_node;
		movig_node = movig_node->next;
		i++;
	}
	return (env_arry);
}

int	sort_string(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] > str2[i])
			return (1);
		else if (str[i] < str2[i])
			return (0);
		i++;
	}
	return (-1);
}

void	sort_nodearr(t_env_var **env_arry, int list_size)
{
	int				i;
	long long int	j;
	t_env_var		*hide;

	j = 0;
	while (j < list_size)
	{
		i = 0;
		while (i < list_size - 1)
		{
			if (sort_string(env_arry[i]->name, env_arry[i + 1]->name))
			{
				hide = env_arry[i];
				env_arry[i] = env_arry[i + 1];
				env_arry[i + 1] = hide;
			}
			i++;
		}
		j++;
	}
}

void	display_export_arry(t_env_var **arry, int size, int fd)
{
	int	i;

	i = 0;
	(void)fd;
	while (i < size)
	{
		if (arry[i]->name[0] == '_')
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(arry[i]->name, 1);
		if (arry[i]->data != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(arry[i]->data, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		i++;
	}
}
