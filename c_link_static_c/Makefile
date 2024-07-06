CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_PATH = src
INC_PATH = ../libmatrix_c/inc
OBJS_PATH = objs
TARGET_DIR = build

SRCS = $(wildcard $(SRCS_PATH)/*.c)
OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(SRCS))

TARGET = $(TARGET_DIR)/main

all: header $(TARGET) lib

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ $(OBJS) -L../libmatrix_c/build -lmatrix_c_static

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
	./$(TARGET)

leaks: all
	valgrind --leak-check=full \
	--show-leak-kinds=all \
    --track-origins=yes \
    ./$(TARGET)

.PHONY: all clean fclean re header run leaks lib lib_dynamic lib_static
