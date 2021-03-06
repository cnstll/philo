NAME = philo

SRCS = srcs/philo.c \
	   srcs/argument_checker.c \
	   srcs/init_simulation.c \
       srcs/life_of_philo.c \
	   srcs/eating.c \
	   srcs/thinking.c \
	   srcs/sleeping.c \
       srcs/death_of_philo.c \
	   srcs/clean_before_exit.c \
	   srcs/utils_1.c \
	   srcs/utils_2.c \
	   srcs/utils_3.c

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang-9
    endif
    ifeq ($(UNAME_S),Darwin)
        CC=clang
    endif

CFLAGS = -Wall -Wextra -Werror -pthread

DFLAG = -g -fsanitize=thread

DLEAKS_FLAG = -g -fsanitize=address


INCLUDES= -I includes/

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(CC) $(CFLAGS) $(DFLAG) -o $(NAME) $(SRCS)

debug_leaks :
	$(CC) $(CFLAGS) $(DLEAKS_FLAG) -o $(NAME) $(SRCS)

clean :
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
