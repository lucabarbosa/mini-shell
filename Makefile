NAME		=	minishell
CC			=	@cc
CFLAGS	=	-Wall -Wextra -Werror
LIBFT		=	libft/libft.a
INC		=	-I ./src -I ./libft
SRC		=	$(MAIN) $(LEXER)

MAIN		=	src/main.c \

LEXER		=	src/lexer/lexer.c \
				src/lexer/tokenizer_utils.c \
				src/lexer/handle_tokens.c \

OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))

all:		$(LIBFT) $(NAME)

$(LIBFT):		
			@make -s -C libft
			@echo "\033[1;32m✅ Libft compiled!\033[1;30m"

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
			@echo "\033[1;32m✅ Minishell compiled!\033[1;30m"

obj/%.o:	src/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LIBFT) obj
			@echo "\033[1;35mObjects deleted.\033[1;30m"

fclean:	clean
			@make -s fclean -C libft
			@rm -rf $(NAME)
			@echo "\033[1;36mMinishell deleted!\033[1;30m"

re:			fclean all

.PHONY:		all clean fclean re
