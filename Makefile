# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namalier  <marvin@42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 19:37:32 by namalier          #+#    #+#              #
#    Updated: 2023/12/16 19:26:21 by namalier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c ft_printf_upper.c

HEADER		= ft_printf.h

OBJS		= ${SRCS:.c=.o}

NAME		= libftprintf.a

CFLAGS		= -Wall -Werror -Wextra

.c.o		:
			cc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}		:    ${OBJS}
			make -C libft
			cp libft/libft.a ${NAME}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all			:		${NAME}

clean		:
			rm -f ${OBJS} libft/*.o libft/*.gch *.gch

fclean		:		clean
			rm -f ${NAME} libft/libft.a

re			: fclean all

exec		: ${SRCS} libft/ft_strlen.c
			cc ${CFLAGS} $^

.PHONY		: all clean fclean re
