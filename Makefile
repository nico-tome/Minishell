NAME := minishell

SRC_DIR := src/
BUILD_DIR := build/

EXEC_DIR := executer/
EXEC_PIPE := execute_pipe/
PARSER_DIR := parser/
PROMPT_DIR := prompt/
LEXER_DIR := lexer/
TOKEN_DIR := token/
BUILTINS_DIR := builtins/
LIBFT = ./src/libft/libft.a
LIBFT_DIR = src/libft

SRCS := $(SRC_DIR)minishell.c \
		$(SRC_DIR)$(PROMPT_DIR)prompt.c \
		$(SRC_DIR)$(TOKEN_DIR)token.c \
		$(SRC_DIR)ft_init_env.c \
		$(SRC_DIR)$(PARSER_DIR)ft_add_cmd.c \
		$(SRC_DIR)$(PARSER_DIR)ft_find_path.c \
		$(SRC_DIR)$(PARSER_DIR)ft_add_cmd.c \
		$(SRC_DIR)$(PARSER_DIR)parser.c \
		$(SRC_DIR)$(EXEC_PIPE)pipeline.c

OBJ := $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRCS))

HEADERS := includes/

CC := cc

FLAGS := -Wall -Werror -Wextra -g

all: ${NAME}

$(NAME): $(LIBFT) ${OBJ}
	${CC} -o ${NAME} -I ${HEADERS} ${OBJ} ${LIBFT} ${FLAGS} -lreadline

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	${CC} -o $@ -I ${HEADERS} -c $< ${FLAGS}

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilation of libft finished !$(NC)"

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	rm -f ${OBJ}

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
