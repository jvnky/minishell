# *** NAME - CC - FLAGS ****************************************************** #

NAME					= 	minishell

CC						= 	gcc

CFLAGS					= 	-MMD  -Wall -Wextra -Werror -I includes #$(LEAKS)\

LEAKS                   =   -g3 -fsanitize=address

BONUS_FLAG				= 	0

TESTER_FLAG				= 	0

LIB						= -lc -lncurses\

#MLX_PATH				= minilibx-linux/

#MLX_NAME				= libmlx.a

#MLX						= $(MLX_PATH)$(MLX_NAME)

# *** PROJECT HEADER ********************************************************* #

HDIR					=	$(addprefix -I, $(HEADER_DIR))

HEAD					=	$(addprefix $(HEADER_DIR), $(HEADER))

HEADER_DIR				=	\
							./include/

HEADER							=	\
									minishell.h \
									parser.h    \
									structure.h \
									structast.h \
									env.h   \

# *** SRCS ******************************************************************* #

SRCS_DIR					=	./srcs/

SRCS_LIST					=	\
							$(MINISHELL) \

MINISHELL                   =	/main/main.c  \
								/main/utils.c   \
								/main/free.c   \
								/parser/expance.c    \
								/parser/parse_built_in.c    \
								/parser/history.c    \
								/parser/parse_double_quote.c    \
								/parser/parse_node.c    \
								/parser/parse_node_utils.c    \
								/parser/parse_simple_quote.c    \
								/parser/parser_command.c    \
								/parser/parser_utils.c \
								/parser/start_parse.c   \
								/parser/treeAST.c   \
								/exec/cd.c  \
								/exec/echo.c    \
								/exec/pwd.c \
								/exec/utils.c   \
								/exec/env.c \
								/exec/exit.c \
								/exec/export.c \
								/exec/unset.c \
								/parser/manipulatething.c\


SRCS                        =	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

DEPS					= $(OBJS:.o=.d)

-include $ (DEPS)

OBJS_DIR				=	./objs/

OBJS_LIST				=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS					=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))



all: $(MLX) $(OBJS) $(SRCS) $(NAME)

$(MLX) :
		@make -sC $(MLX_PATH)

$(NAME): $(OBJS) $(SRCS)
	@ $(CC) $(CFLAGS) $(HDIR) $(OBJS) $(MLX) $(LIB) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(HDIR) -D BONUS=$(BONUS_FLAG) -c -o $@ $<

leak: $(OBJS) $(SRCS)
	@ $(CC) $(CFLAGS) $(LEAKS) $(HDIR) $(OBJS) $(MLX) $(LIB) -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
#	@make clean -C $(MLX_PATH)

re: fclean all

bonus:
	make fclean
	make -j BONUS_FLAG=1

.PHONY: all clean fclean re bonus leak
