# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/12 15:57:17 by budelphi          #+#    #+#              #
#    Updated: 2021/06/12 16:42:47 by budelphi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

INC		=	includes
HEADER	=	includes/philo.h

SRCS	=	srcs/libft_utils.c \
			srcs/philo_utils.c \
			srcs/philo_init.c \
			srcs/philo_parser.c \
			srcs/philo_main.c \
			srcs/simulation.c

OBJ		=	$(SRCS:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(ADD_LIBS)

%.o : %.c	$(INC)
			$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re