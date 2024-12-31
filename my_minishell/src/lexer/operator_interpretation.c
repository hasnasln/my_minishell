/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_interpretation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:23 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 13:55:26 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

void	operator_interpretation(t_shell *shell, char *subarrys)
{
	if (subarrys[0] == '>' && subarrys[1] != '>')
		add_node_cmdlist(shell->all_cmd, crate_opreator(subarrys, RD));
	else if (subarrys[0] == '>' && subarrys[1] == '>')
		add_node_cmdlist(shell->all_cmd, crate_opreator(subarrys, RDD));
	else if (subarrys[0] == '<' && subarrys[1] != '<')
		add_node_cmdlist(shell->all_cmd, crate_opreator(subarrys, RI));
	else if (subarrys[0] == '<' && subarrys[1] == '<')
		add_node_cmdlist(shell->all_cmd, crate_opreator(subarrys, RII));
	else if (subarrys[0] == '|')
		add_node_cmdlist(shell->all_cmd, crate_opreator(subarrys, PIPE));
}
