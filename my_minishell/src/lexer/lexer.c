/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:20 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:33:01 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

void	normalize_spaces(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == ' ' && shell->line[i + 1] == ' ')
		{
			tmp = shell->line;
			shell->line = ft_change(" ", shell->line, i, i + 1);
			free(tmp);
			if (shell->line == NULL)
				my_exit2(1);
			i--;
		}
		i++;
	}
}

char	**split_and_trim(t_shell *shell)
{
	char	**subarrays;
	char	*tmp;
	int		i;

	subarrays = split_include_brackets(shell->line, "|<>");
	if (subarrays == NULL)
		my_exit2(1);
	i = -1;
	while (subarrays[++i])
	{
		tmp = subarrays[i];
		subarrays[i] = ft_strtrim(subarrays[i], " ");
		if (subarrays[i] == NULL)
		{
			subarrays[i] = tmp;
			free_2d(subarrays);
			my_exit2(1);
		}
		free(tmp);
	}
	shell->subarrays = subarrays;
	return (subarrays);
}

static void	convert_line_to_cmd_node(t_shell *shell, char **subarrays)
{
	char	**sub_subarrays;
	int		j;

	j = -1;
	while (subarrays[++j])
	{
		if (j % 2 == 1)
		{
			operator_interpretation(shell, subarrays[j]);
			continue ;
		}
		sub_subarrays = ft_split(subarrays[j], ' ');
		if (sub_subarrays == NULL)
			my_exit2(1);
		shell->sub_subarrays = sub_subarrays;
		expand_env_not_in_text(shell, sub_subarrays);
		put_it_back(shell, sub_subarrays, shell->hides->head, -1);
		put_it_back_rquestins(shell, sub_subarrays);
		add_node_cmdlist(shell->all_cmd,
			create_cmd_node(sub_subarrays, -1, -1));
		free(subarrays[j]);
	}
	free(subarrays);
	shell->subarrays = NULL;
	shell->sub_subarrays = NULL;
}

void	configure_and_run_commands(t_shell *shell, char **subarrays)
{
	shell->all_cmd = init_cmd_list();
	if (shell->all_cmd == NULL)
		my_exit2(1);
	setup_pipes(shell, subarrays);
	convert_line_to_cmd_node(shell, subarrays);
	recent_settings(shell);
	connect_the_pipes(shell);
	heredoc_settings(shell);
	if (shell->flag == 1)
	{
		get_shell()->exit_status = 1;
		shell->flag = 0;
		return ;
	}
	redirection_settings(shell);
	execute_all(shell);
	free_2d_int(shell->al_fd, shell->pipe_count);
	shell->al_fd = NULL;
	shell->pipe_count = 0;
}
