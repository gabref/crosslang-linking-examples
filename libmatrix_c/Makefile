CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS_PATH = src
INC_PATH = inc
OBJS_PATH = objs

SRCS = $(wildcard $(SRCS_PATH)/*.c)
OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(SRCS))

TARGET = build/main

all: header $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ $(OBJS)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)

clean:
	@echo "Cleaning the project..."
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -rf $(TARGET)

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


.PHONY: all clean fclean re header run
