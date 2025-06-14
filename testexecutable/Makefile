NAME	= ../rush-01
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -flto -Ofast -march=native #-g -fsanitize=address  
SRCS	= initialize.c logic_solve.c sudoku.c utilities.c vision.c vision_helpers.c

OBJDIR	= Sudobjects

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:	
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
