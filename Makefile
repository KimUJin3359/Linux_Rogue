CC = gcc
CFLAGS = -Wall -Wextra

TARGET = game

SRCS = main.c game.c monster.c
OBJS = ${SRCS:.c=.o}

${TARGET} : ${OBJS}
	${CC} -o $@ $^ -lncursesw -lpthread

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ./ 
all : ${TARGET}

clean :
	rm -rf *.o

fclean : clean
	rm -rf ${TARGET}

re : fclean all

.PHONY : all clean fclean re
