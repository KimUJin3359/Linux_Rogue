CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = game

SRCS = main.c game.c
OBJS = ${SRCS:.c=.o}

${TARGET} : ${OBJS}
	${CC} -o $@ $^ -lncursesw

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ./ 
all : ${TARGET}

clean :
	rm -rf *.o

fclean : clean
	rm -rf ${TARGET}

re : fclean all

.PHONY : all clean fclean re
