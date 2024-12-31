/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:12 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:16:25 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	expend_dollarquestion(t_shell *shell, char **line, int started)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(shell->exit_status);
	tmp2 = *line;
	*line = ft_change(tmp, *line, started, started + 3);
	if (*line == NULL)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	free(tmp2);
}

void	find_and_expend_env(t_shell *shell, char **text,
		char *name, int baslangic)
{
	char		*tmp;
	t_env_var	*search;

	search = find_envlst_node(shell->env_list, name);
	if (search == NULL)
	{
		tmp = *text;
		*text = ft_change("", *text, baslangic, baslangic + ft_strlen(name));
		if (*text == NULL)
			return ;
		free(tmp);
	}
	else
	{
		tmp = *text;
		*text = ft_change(search->data, *text, baslangic,
				baslangic + ft_strlen(name));
		if (*text == NULL)
			return ;
		free(tmp);
	}
}

char	*env_expend(t_shell *shell, char *line_piece)
{
	int		started;
	char	*name;

	while (1)
	{
		started = find(line_piece, "$", 0);
		if (started == -1)
			return (line_piece);
		if (ft_isdigit(line_piece[started + 1]))
		{
			name = line_piece;
			line_piece = ft_change("", line_piece, started, started + 1);
			if (line_piece == NULL)
				return (NULL);
			free(name);
			continue ;
		}
		name = get_part(line_piece + started + 1,
				"@â~{}^[]/?=:.,-+*%$#!\"\'", 0);
		if (name == NULL)
			return (NULL);
		line_piece = handle_special_variables(shell, line_piece, name, started);
		free(name);
	}
}

char	*expand_inqoute_data(t_shell *shell, char *htext, int flag)
{
	char	*hides_data;
	char	*expanded_data;

	if (htext[0] == '\'' || flag == 1)
	{
		hides_data = smash(htext, 1, ft_strlen(htext) - 2);
		if (hides_data == NULL)
			return (NULL);
		return (hides_data);
	}
	if (htext[0] == '"')
	{
		hides_data = smash(htext, 1, ft_strlen(htext) - 2);
		if (hides_data == NULL)
			return (NULL);
		expanded_data = env_expend(shell, hides_data);
		return (expanded_data);
	}
	return (NULL);
}

void	expand_env_not_in_text(t_shell *shell, char **sub_subarrays)
{
	char	*tmp;
	int		i;

	i = 0;
	while (sub_subarrays[i] != NULL)
	{
		tmp = sub_subarrays[i];
		if (i == 0 && shell->all_cmd->tail != NULL
			&& shell->all_cmd->tail->op_code == RII)
		{
			i++;
			continue ;
		}
		sub_subarrays[i] = env_expend(shell, sub_subarrays[i]);
		if (sub_subarrays[i] == NULL)
		{
			sub_subarrays[i] = tmp;
			my_exit2(1);
		}
		i++;
	}
}
