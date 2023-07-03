NAME		=	minishell

INCLUDE		=	./include

LIBFT		=	lib/libft/libft.a

PRINTF		= 	lib/printf/libftprintf.a

PLATFORM	=	$(shell uname -s)

BUILD		=	./build

SRC			=	./src

DEP			=	$(patsubst %.h, $(INCLUDE)/%.h,\
				debug.h defines.h list.h \
				lex.h tree.h minishell.h) \
				Makefile

SRCS		=	$(patsubst %.c, $(SRC)/Debug/%.c,\
				get_type.c print_messages.c)

SRCS		+=	$(patsubst %.c, $(SRC)/%.c,\
				main.c) \
				$(patsubst %.c, $(SRC)/List/%.c,\
				lst_clear.c lst_get.c lst_last.c \
				lst_new.c lst_pop.c lst_push.c \
				lst_set.c lst_size.c) \
				$(patsubst %.c, $(SRC)/BuiltIns/%.c,\
				history.c env.c pwd.c cd.c unset.c) \
				$(patsubst %.c, $(SRC)/Init/%.c,\
				env_init.c mode_init.c sig_init.c \
				exit.c echo.c export.c) \
				$(patsubst %.c, $(SRC)/Utils/%.c,\
				get_env.c print_logo.c is_token.c) \
				$(patsubst %.c, $(SRC)/Lexer/%.c,\
				word_lists.c operator_token.c \
				quote_token.c word_token.c \
				get_next_token.c lex.c wordl_size.c) \


OBJS		=	$(patsubst %.c, $(BUILD)/%.o, main.c) \
				$(filter-out %.c, $(patsubst $(SRC)/BuiltIns/%.c, $(BUILD)/%.o, $(SRCS))) \
				$(filter-out %.c, $(patsubst $(SRC)/Init/%.c, $(BUILD)/%.o, $(SRCS))) \
				$(filter-out %.c, $(patsubst $(SRC)/Utils/%.c, $(BUILD)/%.o, $(SRCS))) \
				$(filter-out %.c, $(patsubst $(SRC)/List/%.c, $(BUILD)/%.o, $(SRCS))) \
				$(filter-out %.c, $(patsubst $(SRC)/Lexer/%.c, $(BUILD)/%.o, $(SRCS))) \
				$(filter-out %.c, $(patsubst $(SRC)/Debug/%.c, $(BUILD)/%.o, $(SRCS)))

# Compilation options

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

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
YELLOW	=	\033[33m
BLUE	=	\033[34m

# Recipies
all:		wait_msg $(INVOKE) $(NAME)

$(BUILD):
				@mkdir -p $(BUILD)

$(BUILD)/%.o:	$(SRC)/%.c $(DEP)
					@echo "${YELLOW}Compiling $<.${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BUILD)/%.o:	$(SRC)/*/%.c $(DEP)
					@echo "${YELLOW}Compiling $<.${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):	$(BUILD) $(OBJS) $(LIBFT) $(PRINTF)
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
				@echo "${YELLOW}Cleaning Build...${RESET}"
				@$(RM) $(BUILD)
				@echo "${GREEN}Done.${RESET}"

fclean:		libft
				@echo "${YELLOW}Cleaning Everyting...${RESET}"
				@$(RM) $(BUILD)
				@$(RM) $(NAME)
				@echo "${GREEN}Done.${RESET}"

configure:
			./configure.sh readline

re:			fclean all

.PHONY:		all clean fclean re wait_msg libft printf configure
