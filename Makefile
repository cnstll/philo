NAME = philo

SRCS = srcs/philo.c \
	   srcs/argument_checker.c \
	   srcs/utils_1.c \
	   srcs/utils_2.c \
       srcs/life_of_philo.c

OBJS = $(SRCS:.c=.o)

CC = clang-9

CFLAGS = -Wall -Wextra -Werror -pthread

GFLAG = -g3

INCLUDES= -I includes/

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS)

clean :
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
