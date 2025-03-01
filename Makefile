EXECUTABLE	:=	rush01checker

CC			:=	c++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++20 #-g -fsanitize=address

OBJ_DIR		:=	objs

SRCS	 	:=	fork.cpp \
				main.cpp \
				utils.cpp \
				test.cpp \
				vision.cpp \

OBJECTS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:%.cpp=%.o))


all: $(EXECUTABLE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(EXECUTABLE) 

$(OBJ_DIR)/%.o : %.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

retest: fclean test

debug: CPPFLAGS += -g3 -fsanitize=address
debug: re

.PHONY: all clean fclean re test