/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:25:46 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 16:53:36 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../my_lib/libft.h"

# define RD			1
# define RDD		2
# define RI			3
# define RII		4
# define ERII		-4
# define PIPE		5
# define FNAME		6
# define OFNAME		-6 

# define MNODE		-7
# define FNODE		-8
# define WNODE		-9
# define RMNODE		-10	

/*------SIGNAL-TYPE------*/
# define STATE_EMPTY_PROMPT				1
# define STATE_READING_INPUT			2
# define STATE_EXECUTING_COMMAND		3
# define STATE_HEREDOC					4
# define STATE_WAIT_HEREDOC				5

/*---------ENV ---------*/

typedef struct s_env_var
{
	char				*name;
	char				*data;
	struct s_env_var	*prev;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_env_list
{
	int			list_size;
	t_env_var	*head;
	t_env_var	*tail;
}	t_env_list;
/*---------------------------*/

/*---------HİDES---------*/
typedef struct hidden_item_lst_node
{
	char						*data;
	struct hidden_item_lst_node	*next;
}	t_hidden_item_lst_node;

typedef struct hidden_item_lst
{
	t_hidden_item_lst_node	*head;
}	t_hidden_item_lst;
/*------------------------------*/

/*---------CMD-LIST----------*/

typedef struct cmd_list_node
{
	char					**cmd;
	char					*operator;
	int						op_code;
	int						fd_in;
	int						fd_out;
	int						old_fd_in;
	int						old_fd_out;
	pid_t					pid;
	struct cmd_list_node	*next;
	struct cmd_list_node	*prev;
}	t_cmd_list_node;

typedef struct cmd_list
{
	int				cmd_size;
	t_cmd_list_node	*head;
	t_cmd_list_node	*tail;
}	t_cmd_list;
/*------------------------------*/

/*---------Main-Structer----------*/

typedef struct s_shell
{
	int					exit_status;
	int					status;
	int					flag;
	t_env_list			*env_list;
	t_hidden_item_lst	*hides;
	t_cmd_list			*all_cmd;
	char				**env;
	char				**new_enw;
	char				**subarrays;
	char				**sub_subarrays;
	char				*line;
	int					pipe_count;
	int					**al_fd;
}	t_shell;

/*-----------------ENV-LIST----------------*/

t_env_list				*creat_envlst(void);
t_env_var				*create_envlst_node(char *name, char *data);
int						add_envlst_node(t_env_list *env_list, t_env_var *node);
t_env_var				*find_envlst_node(t_env_list *env_list, char *name);
void					free_envlst(t_env_list *env_list);
int						remove_from_envlist(t_env_list *env_list, char *name);
t_env_list				*charptr_to_envlst(char **env);

/*-----------------HİDES-LIST----------------*/

t_hidden_item_lst		*init_hide_item_list(void);
t_hidden_item_lst_node	*create_hide_list_node(char *data);
void					add_hide_list(t_hidden_item_lst *lst, \
	t_hidden_item_lst_node *new_node);
void					pop_first_node(t_hidden_item_lst *lst);
void					free_hidden_item_lst(t_hidden_item_lst *lst, int code);

/*-----------------CMD-LİST-----------------*/

void					add_node_cmdlist(t_cmd_list *cmdlst, \
	t_cmd_list_node *node);
t_cmd_list_node			*create_cmd_node(char **cmd, int cmd_no, int fd_out);
t_cmd_list_node			*crate_opreator(char *cmd, int op_code);
t_cmd_list				*init_cmd_list(void);
void					free_cmd_list(t_cmd_list *list);

/*-------SIGNAL-----*/

void					listen_signal(void);

/*-----------GET-FUNCTİONS------------------*/

t_shell					*get_shell(void);

/*---------LEXER----------*/

int						quotes(char *line);
int						check_special_operator_patterns(char *str);
void					hide_question_marks(t_shell *shell);
void					hide_text(t_shell *shell);
void					normalize_spaces(t_shell *shell);
char					**split_and_trim(t_shell *shell);
void					configure_and_run_commands(t_shell *shell, \
	char **subarrys);
void					recent_settings(t_shell *shell);
void					the_past(t_shell *shell);
void					connect_the_pipes(t_shell *shell);
void					heredoc_settings(t_shell *shell);
int						redirection_settings(t_shell *shell);
void					setup_pipes(t_shell *shell, char **subarrys);
void					operator_interpretation(t_shell *shell, \
	char *subarrys);
void					expand_env_not_in_text(t_shell *shell, \
	char **sub_subarrays);
char					*expand_inqoute_data(t_shell *shell, \
	char *text, int flah);
void					put_it_back(t_shell *shell, char **sub_subarrays, \
	t_hidden_item_lst_node *node, int r);
void					put_it_back_rquestins(t_shell *shell, \
	char **subarrys2);
char					*env_expend(t_shell *shell, char *line_piece);
int						update_cmd_io(t_shell *shell, \
	t_cmd_list_node *node_to_update, int *count);
int						update_fd(t_cmd_list_node *node, \
	t_cmd_list_node *node_to_update);
char					*handle_special_variables(t_shell *shell, \
	char *line_piece, char *name, int started);
void					expend_dollarquestion(t_shell *shell, char **line, \
	int started);
void					find_and_expend_env(t_shell *shell, char **text, \
	char *name, int baslangic);

/*-------------EXECUTE-------------*/

void					execute_heredoc(t_shell *shell, t_cmd_list_node *node, \
	int *fd);
char					**create_new_env(t_shell *shell);
void					execute_myfunction(t_shell *shell, \
	t_cmd_list_node *cmd_n, int fd_in, int fd_out);
int						is_one_of_my_function(char **cmd);
int						execute_pipes(t_shell *shell);
void					execute_others(t_shell *shell, t_cmd_list_node *cmd_n);
void					single_cmd(t_shell *shell, t_cmd_list_node *cmd_n);
void					execute_all(t_shell *shell);
char					*get_paths(t_shell *shell, char *cmd);
void					write_error(char *cmd, char *error, int code);
char					*find_real_path(char **split_r, char *cmd, int flag, \
	char *paths);
int						is_dir(char *path);
char					*get_in_envlst_path_node(t_env_list *env_list);

/*----------------MY-BUILD--------------------*/

int						env(t_shell *minishell, int fd);
int						check_env_args(char **cmd);
int						export(char **cmd, t_shell *minishell, int fd);
t_env_var				**create_export_ary(t_env_list *env_list);
void					display_export_arry(t_env_var **arry, int size, int fd);
void					sort_nodearr(t_env_var **env_arry, int list_size);
int						echo(char **cmd_f, int fd);
int						cd(char **cmd, int fd, t_shell *minishell);
int						pwd(int fd);
int						unset(char **cmd, t_shell *minishell);
void					my_exit(int status);

/*--------------FREE--------------------------------*/

void					my_exit2(int status);
void					clear_circle(t_shell *shell);

/*--------------helper_functions*-----------*/

int						len_and_name_compare(char *str, char *str2);
char					*ft_change(char *new, char *old, int start, int end);
char					*concatenate_substrings(char **str, char c);
void					free_and_null(void **ptr);
void					free_2d(char **str);
void					free_2d_int(int **arr, int size);
int						find(char *src, char *wanted, int start);
int						str_replace(char **src, char *old, char *new);
void					brak_node(t_cmd_list_node *node, char ***p1_address, \
	char ***p2_address, int index);
int						check_builtin_possibility(char *str, char *str2);

/*-------NEW-SPLIT--------*/

char					**split_include_brackets(char *text, char *brackets);
int						bracket_counter(char *text, char *brackets);
int						is_bracket(char c, char *brackets);
char					*smash(char *text, int start, int end);
char					*get_part(char *text, char *brackets, int flag);
void					free_and_null(void **ptr);

#endif