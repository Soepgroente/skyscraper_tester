EXECUTABLE	:=	rush01_checker

CC			:=	cc
CFLAGS		=	-Wall -Wextra -Werror #-g -fsanitize=address

OBJ_DIR		:=	objs

SRCS	 	:=	main.c \
				utils.c \
				vision.c \

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