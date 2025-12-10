NAME		=	minishell
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror
LIBFT		=	libft/libft.a
INC		=	-I ./src -I ./libft
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))
SRC		=	src/main.c

all:		$(LIBFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
			@echo "\n\033[1;32m✅ minishell compiled!"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT):		
			@make -s -C libft
			@echo "Libft compiled!"

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LIBFT) obj
			@echo "\033[1;35mObjects deleted."

fclean:	clean
			@make -s fclean -C libft
			@rm -rf $(NAME)
			@echo "\033[1;36minishell deleted."

re:			fclean all

.PHONY:		all clean fclean re
