/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:07:43 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 16:49:15 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include "../my_include/shell.h"

static void	shell_put_null(t_shell *shell)
{
	shell->line = NULL;
	shell->subarrays = NULL;
	shell->sub_subarrays = NULL;
	shell->new_enw = NULL;
	shell->all_cmd = NULL;
	shell->al_fd = NULL;
}

static void	init_shell(t_shell **shell, char **env)
{
	char	*tmp;

	*shell = get_shell();
	(*shell)->env_list = charptr_to_envlst(env);
	(*shell)->hides = init_hide_item_list();
	(*shell)->env = env;
	(*shell)->status = 0;
	(*shell)->exit_status = 0;
	(*shell)->pipe_count = 0;
	(*shell)->flag = 0;
	shell_put_null(*shell);
	if (find_envlst_node((*shell)->env_list, "PWD") == NULL)
	{
		if (!add_envlst_node((*shell)->env_list,
				create_envlst_node(ft_strdup("PWD"), getcwd(NULL, 0))))
			my_exit(1);
	}
	else
	{
		tmp = find_envlst_node((*shell)->env_list, "PWD")->data;
		(find_envlst_node((*shell)->env_list, "PWD"))->data
			= getcwd(NULL, 0);
		free(tmp);
	}
}

static void	main_helper(t_shell *shell)
{
	add_history(shell->line);
	shell->status = STATE_READING_INPUT;
	if (quotes(shell->line))
	{
		write(2, "bash: syntax error\n", 19);
		shell->exit_status = 258;
		clear_circle(shell);
		return ;
	}
	hide_question_marks(shell);
	hide_text(shell);
	if (check_special_operator_patterns(shell->line))
	{
		write(2, "bash: syntax error\n", 19);
		shell->exit_status = 258;
		clear_circle(shell);
		return ;
	}
	normalize_spaces(shell);
	configure_and_run_commands(shell, split_and_trim(shell));
	clear_circle(shell);
}

int	main(int argc, char **arg, char **env2)
{
	t_shell	*shell;

	(void)arg;
	(void)argc;
	init_shell(&shell, env2);
	listen_signal();
	while (42)
	{
		shell->status = STATE_EMPTY_PROMPT;
		shell->line = readline("\x1b[32mmah -> \x1b[0m");
		if (!shell->line)
			my_exit(shell->exit_status);
		if (shell->line[0] == '\0')
			clear_circle(shell);
		else
			main_helper(shell);
	}
}
