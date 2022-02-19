
NAME	=	philo
 
CC		=	gcc
CFLAGS	=	-pthread -Wall -Wextra -Werror -g
IFLAGS	=	-I. -I includes
BFLAGS	=	0
 
SRC	=				srcs/main.c \
					srcs/routine.c \
					srcs/status.c \
					srcs/init.c \
					srcs/lib_func.c \

OBJ		=	$(SRC:%.c=%.o)
 
%.o: %.c
			$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -D BONUS=$(BFLAGS)
 
ifeq ($(shell uname), Linux)
$(NAME): IFLAGS = -I. 
endif
 
$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) $(IFLAGS) $(LFLAGS) -o $@
 
 
all:		$(NAME)

 
clean:
			rm -rf $(OBJ)
 
ifeq ($(shell uname), Linux)
endif
 
fclean:		clean
			rm -rf $(NAME)
 
re:			fclean all
 
.PHONY: all clean fclean re
 
