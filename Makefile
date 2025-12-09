NAME := minishell

SRC_DIR := src/
BUILD_DIR := build/

SRCS := $(SRC_DIR)minishell.c

OBJ := $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRCS))

HEADERS := includes/

CC := cc

FLAGS := -Wall -Werror -Wextra -Iincludes/ast -Iincludes/debug -Iincludes/parsing -Iincludes/shell -Iincludes -g

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
