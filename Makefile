NAME := minishell

SRC_DIR := src/
BUILD_DIR := build/
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
PURPLE=\033[0;35m
NC=\033[0m
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
		$(SRC_DIR)$(TOKEN_DIR)verify_tokens.c \
		$(SRC_DIR)$(TOKEN_DIR)free_tokens.c \
		$(SRC_DIR)ft_init_env.c \
		$(SRC_DIR)$(PARSER_DIR)ft_add_cmd.c \
		$(SRC_DIR)$(PARSER_DIR)ft_find_path.c \
		$(SRC_DIR)$(PARSER_DIR)parser.c \
		$(SRC_DIR)$(EXEC_PIPE)pipeline.c \
		$(SRC_DIR)$(EXEC_PIPE)env_utils.c

OBJ := $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRCS))

HEADERS := includes/

CC := cc

FLAGS := -Wall -Werror -Wextra -g

all: ${NAME}

$(NAME): $(LIBFT) ${OBJ}
	@echo "$(GREEN)✅ Compilation of Minishell finished !$(NC)"
	@${CC} -o ${NAME} -I ${HEADERS} ${OBJ} ${LIBFT} ${FLAGS} -lreadline

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	@${CC} -o $@ -I ${HEADERS} -c $< ${FLAGS}

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilation of libft finished !$(NC)"

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -f ${OBJ}

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
