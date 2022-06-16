SRCS	=	pipex.c\
			child.c\
			ft_split.c\
			str_utils.c\
			files.c\
			parse.c\
			get_next_line.c\
			get_next_line_utils.c\
			error.c\
			free.c

OBJS	= ${SRCS:.c=.o}

HEAD	= includes

NAME	= pipex

GCC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o:		%.c
		${GCC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		${GCC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
		${RM} ${OBJS} ${OBJSB}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

bonus:		${NAME}

.PHONY:		all clean fclean re bonus
