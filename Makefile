EXECUTABLE	:=	rush01checker

CC			:=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++20 #-g -fsanitize=address

OBJ_DIR		:=	objs

SRCS	 	:=	fork.cpp \
				main.cpp \
				utils.cpp \
				test.cpp \
				vision.cpp \

OBJECTS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))


all: $(EXECUTABLE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) 

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

retest: fclean test

.PHONY: all clean fclean re test