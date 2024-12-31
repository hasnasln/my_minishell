/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_envarry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:05:09 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 17:49:27 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

char	*increment_shlvl(const char *data)
{
	char	*tmp2;

	tmp2 = ft_itoa(ft_atoi(data) + 1);
	if (tmp2 == NULL)
		my_exit2(1);
	return (tmp2);
}

char	*create_env_entry(const char *name, const char *data)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		my_exit2(1);
	if (data != NULL)
		result = ft_strjoin(tmp, data);
	else
		result = ft_strdup(tmp);
	free(tmp);
	if (result == NULL)
		my_exit2(1);
	return (result);
}

void	create_new_env_helper(t_shell *shell, t_env_var *node,
		char **new_env, int i)
{
	char	*tmp2;

	(void)shell;
	while (node != NULL)
	{
		if (len_and_name_compare(node->name, "SHLVL"))
		{
			tmp2 = increment_shlvl(node->data);
			new_env[i] = create_env_entry(node->name, tmp2);
			free(tmp2);
		}
		else
			new_env[i] = create_env_entry(node->name, node->data);
		node = node->next;
		i++;
	}
}

char	**create_new_env(t_shell *shell)
{
	t_env_var	*node;
	char		**new_env;
	int			i;

	node = shell->env_list->head;
	new_env = (char **)malloc(sizeof(char *)
			* (shell->env_list->list_size + 1));
	if (new_env == NULL)
		my_exit2(1);
	new_env[shell->env_list->list_size] = NULL;
	i = 0;
	create_new_env_helper(shell, node, new_env, i);
	return (new_env);
}
