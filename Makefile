NAME := minishell

SRC_DIR := src/
BUILD_DIR := build/

EXEC_DIR := executer/
PARSER_DIR := parser/
PROMPT_DIR := prompt/
LEXER_DIR := lexer/
BUILTINS_DIR := builtins/

SRCS := $(SRC_DIR)minishell.c \
		$(SRC_DIR)$(PROMPT_DIR)prompt.c

OBJ := $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRCS))

HEADERS := includes/

CC := cc

FLAGS := -Wall -Werror -Wextra -g

all: ${NAME}

$(NAME): ${OBJ}
	${CC} -o ${NAME} -I ${HEADERS} ${OBJ} ${FLAGS} -lreadline

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	${CC} -o $@ -I ${HEADERS} -c $< ${FLAGS}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
