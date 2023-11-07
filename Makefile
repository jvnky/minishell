# *** NAME - CC - FLAGS ****************************************************** #

NAME					= 	minishell

CC						= 	gcc

CFLAGS					= 	 -Wall -Wextra -Werror  -I includes -g

LFLAGS					= 	 -L -lft -lreadline

LEAKS					=	#-g3 -fsanitize=address

BONUS_FLAG				= 	0

TESTER_FLAG				= 	0

LIB						=	-lc -lncurses\

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
									ast.h \

# *** SRCS ******************************************************************* #

SRCS_DIR					=	./srcs/

SRCS_LIST					=	\
							$(MINISHELL) \

MINISHELL                   =	/main/main.c  \
								/main/main_utils.c \
								/main/ft_itoa.c  \
								/main/init.c  \
								/main/utils.c   \
								/main/free.c   \
								/parser/expance.c    \
								/parser/parse_built_in.c    \
								/parser/parse_double_quote.c    \
								/parser/parse_node.c    \
								/parser/parse_node_utils.c    \
								/parser/parser_command.c    \
								/parser/parse_echo_utils.c    \
								/parser/parser_utils.c \
								/parser/start_parse.c   \
								/ast/treeAST.c   \
								/exec/cd.c  \
								/exec/cd_option.c  \
								/exec/echo.c    \
								/exec/pwd.c \
								/exec/utils.c   \
								/exec/env.c \
								/exec/export.c \
								/exec/unset.c \
								/ast/manipulatething.c \
								/ast/manipulate_utils.c \
								/ast/dollar_utils.c \
								/signal/signal.c \
								/ast/mani_split.c \
								/ast/absolut_path.c \
								/ast/exec_ast.c \
								/ast/exec_ast_utils.c \
								/ast/lovenorm.c \
								/ast/loveone.c \
								/ast/lovetwo.c \
								/ast/lovethree.c \
								/ast/astnorm.c \
								/ast/astnormone.c \
								/ast/execbuilt.c \
								/exec/cd_utils.c \
								/ast/exec_builtin_utils.c \
								/ast/exec_exit.c \

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
	@ $(CC) $(CFLAGS) $(LEAKS) $(HDIR) $(OBJS) $(MLX) $(LIB) -o $@ $(LFLAGS)

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
