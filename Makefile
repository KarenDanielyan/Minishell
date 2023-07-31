NAME		=	minishell

INCLUDE		=	./include

LIBFT		=	lib/libft/libft.a

PRINTF		= 	lib/printf/libftprintf.a

PLATFORM	=	$(shell uname -s)

BUILD		=	./build

SRC			=	./src

SUBDIRS		=	BuiltIns Debug Expansions \
				Init Lexer List Parse Utils \
				Preprocessor Execute

DEP			=	$(patsubst %.h, $(INCLUDE)/%.h,\
				debug.h defines.h list.h \
				lex.h minishell.h parser.h \
				execute.h init.h) \
				Makefile

SRCS		=	$(patsubst %.c, $(SRC)/Debug/%.c,\
				get_type.c print_messages.c \
				tree_print.c tree_print_utils.c \
				print_value.c)

SRCS		+=	$(patsubst %.c, $(SRC)/%.c,\
				main.c) \
				$(patsubst %.c, $(SRC)/List/%.c,\
				lst_clear.c lst_get.c lst_last.c \
				lst_new.c lst_pop.c lst_push.c \
				lst_set.c lst_size.c flist.c \
				wordl.c wordl_2.c wordl_3.c) \
				$(patsubst %.c, $(SRC)/BuiltIns/%.c,\
				history.c env.c pwd.c cd.c unset.c \
				echo.c exit.c export.c set.c) \
				$(patsubst %.c, $(SRC)/Init/%.c,\
				env_init.c mode_init.c sig_init.c \
				input.c init.c builtin_init.c) \
				$(patsubst %.c, $(SRC)/Utils/%.c,\
				get_env.c print_logo.c is_token.c \
				var_asign.c visit.c my_fork.c \
				set_ecode.c close_fifo.c print.c \
				search.c) \
				$(patsubst %.c, $(SRC)/Lexer/%.c,\
				word_lists.c operator_token.c \
				word_token.c lex.c \
				get_next_token.c check_tokens.c) \
				$(patsubst %.c, $(SRC)/Parse/%.c,\
				parser.c parse_functions.c \
				node_list.c parse_functions_2.c \
				parse_functions_3.c parse_functions_4.c \
				constructors.c constructors_2.c \
				constructors_3.c error.c drop.c \
				check_syntax.c node_list_2.c here_doc.c \
				here_doc_utils.c) \
				$(patsubst %.c, $(SRC)/Expansions/%.c,\
				expand.c tilde_expand.c parm_exp.c \
				quote_removal.c field_splitting.c \
				join.c glob_exp.c wildcard_match.c \
				parm_utils.c) \
				$(patsubst %.c, $(SRC)/Preprocessor/%.c,\
				preprocess.c) \
				$(patsubst %.c, $(SRC)/Execute/%.c,\
				execute.c exec_functions.c exec_utils.c \
				exec_functions_2.c exec_functions_3.c \
				exec_functions_4.c exec_functions_5.c \
				simple_cmd_handler.c)

OBJS		=	$(foreach dir, $(SUBDIRS), \
				$(patsubst $(SRC)/$(dir)/%.c, $(BUILD)/%.o, \
				$(filter $(SRC)/$(dir)/%.c, $(SRCS)))) \
				$(patsubst %.c, $(BUILD)/%.o, main.c)

# Compilation options

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror -g

INVOKE		=	libft printf

LFLAGS		=	-Llib/libft -lft -Llib/printf -lftprintf -Llib/readline/lib -lreadline -lhistory

ifeq ($(PLATFORM), Linux)
	LFLAGS	+=	-ltinfo
endif

IFLAGS		=	-Iinclude -Ilib/libft -Ilib/printf/include -Ilib/readline/include

MGOALS		=	$(filter-out bonus, $(MAKECMDGOALS))

# Colors

RESET	=	\033[0m
RED		=	\033[31m
GREEN	=	\033[32m
CYAN	=	\033[36m
BLUE	=	\033[34m

# Recipies
all:		wait_msg $(INVOKE) $(NAME)

$(BUILD):
				@mkdir -p $(BUILD)

$(BUILD)/%.o:	$(SRC)/%.c $(DEP)
					@echo "${CYAN}Compiling $<.${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BUILD)/%.o:	$(SRC)/*/%.c $(DEP)
					@echo "${CYAN}Compiling $<.${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):	$(BUILD) $(OBJS) $(LIBFT) $(PRINTF)
				@cp -f $(NAME) $(NAME)_old 2> /dev/null || :
				@echo "${GREEN}Building minishell.${RESET}"
				@$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) -o $(NAME) $(LFLAGS)
				@echo "${GREEN}Build Successfull.${RESET}"

libft:
				@$(MAKE) $(MGOALS) -C lib/libft

printf:
				@$(MAKE) $(MGOALS) -C lib/printf

wait_msg:
				@echo "${BLUE}Please wait for minishell to compile.${RESET}"

clean:		$(INVOKE)
				@echo "${CYAN}Cleaning Build...${RESET}"
				@$(RM) $(BUILD)
				@echo "${GREEN}Done.${RESET}"

fclean:		$(INVOKE)
				@echo "${CYAN}Cleaning Everyting...${RESET}"
				@$(RM) $(BUILD)
				@$(RM) $(NAME) $(NAME)_old
				@echo "${GREEN}Done.${RESET}"

configure:
			./configure.sh readline

re:			fclean all

.PHONY:		all clean fclean re wait_msg libft printf configure
