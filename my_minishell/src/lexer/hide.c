/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:18 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:28:42 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	hide_question_marks(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == '?')
		{
			tmp = shell->line;
			shell->line = ft_change("-?-", shell->line, i, i);
			free_and_null((void *)&tmp);
			if (shell->line == NULL)
				my_exit2 (1);
			i += 2;
		}
		i++;
	}
}

void	quote_to_question(t_shell *shell, int i, char quote)
{
	int						j;
	char					*tmp;
	t_hidden_item_lst_node	*node;

	j = i + 1;
	while (shell->line[j] != quote)
		j++;
	tmp = smash(shell->line, i, j);
	if (tmp == NULL)
		my_exit2(1);
	node = create_hide_list_node(tmp);
	if (node == NULL)
	{
		free(tmp);
		my_exit2(1);
	}
	add_hide_list(shell->hides, node);
	tmp = shell->line;
	shell->line = ft_change("??", shell->line, i, j);
	free(tmp);
	if (shell->line == NULL)
		my_exit2(1);
}

void	hide_text(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->line[++i])
	{
		if (shell->line[i] == '\'')
			quote_to_question(shell, i, '\'');
		else if (shell->line[i] == '"')
			quote_to_question(shell, i, '"');
	}
}
