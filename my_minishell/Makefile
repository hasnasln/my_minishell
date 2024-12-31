NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror


SRC_ENV =	src/env/env_list_functions.c\
			src/env/env_list_functions2.c\


SRC_BUILD =	src/my_build/exit.c\
			src/my_build/echo.c\
			src/my_build/env.c\
			src/my_build/unset.c\
			src/my_build/export.c\
			src/my_build/export_arry.c\
			src/my_build/pwd.c\
			src/my_build/cd.c\


SRC_RD =	src/redirection/redirection_settings.c\
			src/redirection/heredoc_settings.c\
			src/redirection/redirection_helper.c\


SRC_HELPER =	src/helper_functions/concatenate_substrings.c\
				src/helper_functions/free_and_null.c\
				src/helper_functions/free2d.c\
				src/helper_functions/ft_change.c\
				src/helper_functions/ft_split_include_brackets.c\
				src/helper_functions/len_and_name_compare.c\
				src/helper_functions/clear_circle.c\
				src/helper_functions/ft_find.c\
				src/helper_functions/str_replace.c\
				src/helper_functions/get_functions.c\


SRC_MYLIB =	my_lib/ft_strlen.c \
			my_lib/ft_strncmp.c \
			my_lib/ft_putstr_fd.c \
			my_lib/ft_strjoin.c \
			my_lib/ft_strtrim.c \
			my_lib/ft_itoa.c \
			my_lib/ft_split.c \
			my_lib/ft_strchr.c \
			my_lib/ft_memcpy.c \
			my_lib/ft_strdup.c \
			my_lib/ft_isdigit.c \
			my_lib/ft_isalpha.c \
			my_lib/ft_calloc.c \
			my_lib/ft_bzero.c \
			my_lib/ft_atoi.c \
			my_lib/ft_substr.c \



SRC_LEXER =	src/lexer/hide_list.c\
			src/lexer/validate_quotes.c\
			src/lexer/hide.c\
			src/lexer/lexer.c\
			src/lexer/cmd_list.c\
			src/lexer/cmd_list_helper.c\
			src/lexer/setup_pipes.c\
			src/lexer/operator_interpretation.c\
			src/lexer/expand_envs.c\
			src/lexer/put_it_back.c\
			src/lexer/recent_settings.c\
			src/lexer/the_past.c\
			src/lexer/expand_envs_helper.c\


SRC_EXECUTE =	src/execute/execute_heredoc.c\
				src/execute/execute.c\
				src/execute/execute_others.c\
				src/execute/run_my_build.c\
				src/execute/create_new_envarry.c\
				src/execute/execute_single.c\
				src/execute/get_paths.c\
				src/execute/execute_pipes.c\

SRC_PARSE = src/parse/parse.c\



SRC =	src/main.c\
		src/listen_signal.c\
		$(SRC_MYLIB)\
		$(SRC_HELPER)\
		$(SRC_ENV)\
		$(SRC_LEXER)\
		$(SRC_BUILD)\
		$(SRC_RD)\
		$(SRC_EXECUTE)\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONNY: all clean fclean re
