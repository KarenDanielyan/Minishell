NAME		=	minishell

INCLUDE		=	./include

BUILD		=	./build

SRC			=	./src

SUBDIRS		=	Builtins Init input

DEP			=	$(patsubst %.h, $(INCLUDE)/%.h,\
				) Makefile

SRCS		=	$(patsubst %.c, $(SRC)/%.c,\
				main.c) \
				$(patsubst %.c, $(SRC)/BuiltIns/%.c,\
				history.c)

OBJS		=	$(patsubst %.c, $(BUILD)/%.o,\
				main.c) \
				$(filter-out %.c, $(patsubst $(SRC)/BuiltIns/%.c, $(BUILD)/%.o, $(SRCS)))

# Compilation options

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address

INVOKE		=	libft

LFLAGS		=	-L./libft -lft -L/usr/local/lib -lreadline

IFLAGS		=	-I./include -I./libft -I/usr/local/include

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

$(NAME):	$(BUILD) $(OBJS)
				@echo "${GREEN}Building minishell.${RESET}"
				@$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) -o $(NAME) $(LFLAGS)
				@echo "${GREEN}Build Successfull.${RESET}"

libft:
				@$(MAKE) $(MGOALS) -C libft

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

re:			fclean all

.PHONY:		wait_msg libft fclean clean all re
