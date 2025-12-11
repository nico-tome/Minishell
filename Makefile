NAME := minishell

ESC := \033
RESET := $(ESC)[0m
TEXT_CYAN := $(ESC)[38;5;51m
TEXT_BLUE := $(ESC)[38;5;39m
TEXT_DARK_BLUE := $(ESC)[38;5;21m
TEXT_PURPLE := $(ESC)[38;5;93m
TEXT_NEON_GREEN := $(ESC)[38;5;46m
TEXT_NEON_RED := $(ESC)[38;5;196m
BG_RESET := $(RESET)
BG_FRA_BLUE := $(ESC)[48;5;19m
BG_FRA_WHITE := $(ESC)[48;5;255m
BG_FRA_RED := $(ESC)[48;5;160m
BG_BRA_GREEN := $(ESC)[48;5;28m
BG_BRA_YELLOW := $(ESC)[48;5;220m
BG_BRA_BLUE := $(ESC)[48;5;21m
BG_ESP_RED := $(ESC)[48;5;160m
BG_ESP_YELLOW := $(ESC)[48;5;220m
YELLOW=\033[0;33m

SRC_DIR := src/
BUILD_DIR := build/
EXEC_DIR := executer/
EXEC_PIPE := execute_pipe/
PARSER_DIR := parser/
PROMPT_DIR := prompt/
LEXER_DIR := lexer/
TOKEN_DIR := token/
SIGNAL_DIR := signal/
BUILTINS_DIR := built-in/
LIBFT = ./src/libft/libft.a
LIBFT_DIR = src/libft

SRCS := $(SRC_DIR)minishell.c \
		$(SRC_DIR)$(PROMPT_DIR)prompt.c \
		$(SRC_DIR)$(TOKEN_DIR)token.c \
		$(SRC_DIR)$(TOKEN_DIR)verify_tokens.c \
		$(SRC_DIR)$(TOKEN_DIR)free_tokens.c \
		$(SRC_DIR)$(SIGNAL_DIR)signal.c \
		$(SRC_DIR)ft_init_env.c \
		$(SRC_DIR)$(PARSER_DIR)ft_add_cmd.c \
		$(SRC_DIR)$(PARSER_DIR)ft_find_path.c \
		$(SRC_DIR)$(PARSER_DIR)parser.c \
		$(SRC_DIR)$(EXEC_PIPE)pipeline.c \
		$(SRC_DIR)$(EXEC_PIPE)env_utils.c \
		$(SRC_DIR)$(EXEC_DIR)$(BUILTINS_DIR)exit.c

OBJ := $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRCS))

HEADERS := includes/

CC := cc

FLAGS := -Wall -Werror -Wextra -g

all: header ${NAME}

header:
	@echo ""
	@printf " $(TEXT_CYAN)%s$(RESET)\n" ' ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     '
	@printf " $(TEXT_CYAN)%s$(RESET)\n" ' ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     '
	@printf " $(TEXT_BLUE)%s$(RESET)\n" ' ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     '
	@printf " $(TEXT_BLUE)%s$(RESET)\n" ' ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     '
	@printf " $(TEXT_DARK_BLUE)%s$(RESET)\n" ' ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗'
	@printf " $(TEXT_DARK_BLUE)%s$(RESET)\n" ' ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝'
	@echo ""
	@echo ""
	@printf "       $(BG_BRA_GREEN)    $(BG_BRA_YELLOW)  $(BG_BRA_GREEN)    $(BG_RESET)           $(BG_FRA_BLUE)    $(BG_FRA_WHITE)    $(BG_FRA_RED)    $(BG_RESET)           $(BG_ESP_RED)            $(RESET)\n"
	@printf "       $(BG_BRA_GREEN)  $(BG_BRA_YELLOW)  $(BG_BRA_BLUE)  $(BG_BRA_YELLOW)  $(BG_BRA_GREEN)  $(BG_RESET)           $(BG_FRA_BLUE)    $(BG_FRA_WHITE)    $(BG_FRA_RED)    $(BG_RESET)           $(BG_ESP_YELLOW)            $(RESET)\n"
	@printf "       $(BG_BRA_GREEN)    $(BG_BRA_YELLOW)  $(BG_BRA_GREEN)    $(BG_RESET)           $(BG_FRA_BLUE)    $(BG_FRA_WHITE)    $(BG_FRA_RED)    $(BG_RESET)           $(BG_ESP_RED)            $(RESET)\n"
	@echo ""

$(NAME): $(LIBFT) ${OBJ}
	@echo "$(TEXT_NEON_GREEN)✅ Compilation of Minishell finished !$(RESET)"
	@${CC} -o ${NAME} -I ${HEADERS} ${OBJ} ${LIBFT} ${FLAGS} -lreadline

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	@${CC} -o $@ -I ${HEADERS} -c $< ${FLAGS}

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(TEXT_NEON_GREEN)✅ Compilation of libft finished !$(RESET)"

clean:
	@echo "$(YELLOW)🧹 file .o cleaned successfully $(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -f ${OBJ}

fclean: clean
	@echo "$(TEXT_NEON_RED)🧨 minishell deleted$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
