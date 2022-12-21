# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 15:12:33 by hcolumbu          #+#    #+#              #
#    Updated: 2022/10/25 16:21:48 by hcolumbu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	get_next_line.c\
			ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c\
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c\
			ft_memmove.c ft_memset.c ft_strlen.c ft_tolower.c\
			ft_toupper.c ft_memchr.c ft_memcmp.c ft_strlcpy.c\
			ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
			ft_strcmp.c \
			ft_strnstr.c ft_calloc.c ft_strdup.c ft_putchar_fd.c\
			ft_putstr_fd.c ft_putnbr_fd.c ft_substr.c\
			ft_putendl_fd.c ft_strjoin.c ft_strtrim.c\
			ft_itoa.c ft_striteri.c ft_strmapi.c ft_split.c\
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
			ft_lstclear.c ft_lstiter.c ft_lstmap.c\

HEADER	=	libft.h 

OBJ		=	$(patsubst %.c,%.o,$(SRCS))

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)
RM		= 	rm -f

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			ar rcs $(NAME) $?

%.o		:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@
	
clean	:
			$(RM) $(OBJ) $(OBJ_B)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
