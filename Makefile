NAME		=	minishell
CC			=	@cc
CFLAGS	=	-Wall -Wextra -Werror
READLINE =	-lreadline
LIBFT		=	libft/libft.a
INC		=	-I ./src -I ./libft
SRC		=	$(MAIN) $(LEXER) $(PARSER) $(EXECUTOR) $(BUILTIN)

MAIN		=	src/main.c \
				src/minishell_utils.c

LEXER		=	src/lexer/lexer.c \
				src/lexer/tokenizer_utils.c \
				src/lexer/handle_tokens.c \

PARSER		=	src/parser/parser.c \
				src/parser/parser_utils.c \

EXECUTOR	=	src/executor/executor.c \
				src/executor/get_path.c \
				src/executor/handle_redirect.c \
				src/executor/exec_pipes.c \

BUILTIN		=	src/builtin/builtin.c \
					src/builtin/builtin_pwd.c \
					src/builtin/builtin_cd.c \
					src/builtin/builtin_echo.c \
					src/builtin/builtin_unset.c \
					src/builtin/builtin_env.c \
					src/builtin/builtin_exit.c

OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))

all:		$(LIBFT) $(NAME)

$(LIBFT):		
			@make -s -C libft
			@echo "\033[1;32m✅ Libft compiled!\033[1;30m"

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(READLINE)
			@echo "\033[1;32m✅ Minishell compiled!\033[1;30m"

obj/%.o:	src/%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LIBFT) obj
			@echo "\033[1;35m🗑️  Objects deleted.\033[1;30m"

fclean:	clean
			@make -s fclean -C libft
			@rm -rf $(NAME)
			@echo "\033[1;36m🗑️  Minishell deleted!\033[1;30m"

re:			fclean all

val:			re
				@echo "\033[1;31m\n================ Running with valgrind ================\033[1;30m"
				@valgrind --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp ./minishell

.PHONY:		all clean fclean re val
