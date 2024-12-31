/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:17 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 11:35:00 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

int	env(t_shell *shell, int fd)
{
	t_env_var	*node;

	node = shell->env_list->head;
	while (node != NULL)
	{
		if (node->data == NULL)
		{
			node = node->next;
			continue ;
		}
		ft_putstr_fd(node->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(node->data, fd);
		ft_putstr_fd("\n", fd);
		node = node->next;
	}
	return (0);
}

int	check_env_args(char **cmd)
{
	if (cmd[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		get_shell()->exit_status = 1;
		return (0);
	}
	return (1);
}
