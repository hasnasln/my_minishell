/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:34 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 16:19:42 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

int	check_unset_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(cmd[0]))
		return (-1);
	while (cmd[i] != '\0')
	{
		if (ft_isalpha(cmd[i]) == 0 && cmd[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	unset(char **cmd, t_shell *minishell)
{
	int		i;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (check_unset_cmd(cmd[i]) == -1)
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			get_shell()->exit_status = 1;
			i++;
			continue ;
		}
		remove_from_envlist(minishell->env_list, cmd[i]);
		i++;
	}
	return (0);
}
