CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_PATH = src
INC_PATH = ../libmatrix_c/inc
OBJS_PATH = objs
TARGET_DIR = build

SRCS = $(wildcard $(SRCS_PATH)/*.c)
OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(SRCS))

TARGET = $(TARGET_DIR)/libmy_matrix.so

all: header $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -shared -o $@ $(OBJS) -L../libmatrix_c/build -lmatrix_c_static

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)

clean: header
	@echo "Cleaning the project..."
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -rf $(TARGET_DIR)

re: fclean 
	@make all -s

header:
	@echo "Building the project..."

run: all
	python3 test_lib.py

leaks: all
	valgrind --leak-check=full \
	--show-leak-kinds=all \
    --track-origins=yes \
    ./$(TARGET)

.PHONY: all clean fclean re header run leaks
