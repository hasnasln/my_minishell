/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_it_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:26 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 17:46:27 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	put_it_back(t_shell *shell, char **sub_subarrays,
	t_hidden_item_lst_node *tmp, int r)
{
	char					*hides_data;
	int						result;

	while (sub_subarrays[++r])
	{
		while (tmp != NULL)
		{
			if (r == 0 && shell->all_cmd->tail != NULL
				&& shell->all_cmd->tail->op_code == RII)
				hides_data = expand_inqoute_data(shell, tmp->data, 1);
			else
				hides_data = expand_inqoute_data(shell, tmp->data, 0);
			if (hides_data == NULL)
				my_exit2(1);
			result = str_replace(&sub_subarrays[r], "??", hides_data);
			free(hides_data);
			if (result == -2)
				my_exit2(1);
			else if (result == -1)
				break ;
			pop_first_node(shell->hides);
			tmp = shell->hides->head;
		}
	}
}

void	put_it_back_rquestins(t_shell *shell, char **sub_subaryys)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	(void)shell;
	while (sub_subaryys[i])
	{
		j = 0;
		while (sub_subaryys[i][j])
		{
			j = find(sub_subaryys[i], "-?-", j);
			if (j == -1)
				break ;
			tmp = sub_subaryys[i];
			sub_subaryys[i] = ft_change("?", sub_subaryys[i], j, j + 2);
			if (sub_subaryys[i] == NULL)
				my_exit2(1);
			free(tmp);
			j = j + 1;
		}
		i++;
	}
}
