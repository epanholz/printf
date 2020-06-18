# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz       #+#    #+#                 #
#    Updated: 2020/01/29 14:26:28 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	ft_printf.c ft_arguments.c ft_get_utils.c ft_atoi_itoa.c ft_padding.c

INC = ft_printf.h

CC = gcc -Wall -Wextra -Werror

OBJ =$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
