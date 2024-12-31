/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:09 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 11:24:59 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_include/shell.h"

char	*handle_special_variables(t_shell *shell, char *line_piece,
		char *name, int started)
{
	if (ft_strlen(name) == 0 && line_piece[started + 1] == '-' \
			&& line_piece[started + 2] == '?' && line_piece[started + 3] == '-')
		expend_dollarquestion(shell, &line_piece, started);
	else
		find_and_expend_env(shell, &line_piece, name, started);
	return (line_piece);
}
