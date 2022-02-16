# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 15:21:56 by jrobert           #+#    #+#              #
#    Updated: 2021/12/07 16:08:33 by jrobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= 	ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_lstadd_back.c \
					ft_lstadd_front.c \
					ft_lstclear.c \
					ft_lstdelone.c \
					ft_lstiter.c \
					ft_lstlast.c \
					ft_lstnew.c \
					ft_lstsize.c \
					ft_get_next_line.c
					
OBJS			= 	$(addprefix srcs/,$(SRCS:%.c=%.o))
CFLAGS			= 	-Wall -Wextra -Werror -I includes
LIB				= 	libft.a
		
$(LIB)			:	$(OBJS)
					ar rcs $(LIB) $(OBJS)

all    			:	$(LIB)

clean 			:	
					rm -f $(OBJS)

fclean 			:	clean
					rm -f $(LIB) a.out

re				:	fclean all	
