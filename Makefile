NAME		=	minishell
CC			=	@cc
CFLAGS	=	-Wall -Wextra -Werror
LIBFT		=	libft/libft.a
INC		=	-I ./src -I ./libft
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))
SRC		=	src/main.c

all:		$(LIBFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
			@echo "\033[1;32m✅ minishell compiled!\033[1;32m"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT):		
			@make -s -C libft
			@echo "\033[1;32m✅ Libft compiled!\033[1;32m"

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LIBFT) obj
			@echo "\033[1;35mObjects deleted.\033[1;35m"

fclean:	clean
			@make -s fclean -C libft
			@rm -rf $(NAME)
			@echo "\033[1;36mMinishell deleted!\033[1;36m"

re:			fclean all

.PHONY:		all clean fclean re
