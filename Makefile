# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 21:22:18 by afogonca          #+#    #+#              #
#    Updated: 2024/11/16 21:23:48 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = ./libs/libft/libft.a
RM = rm -f

NAME_SERVER = server
OBJS_SERVER = ${SRCS_SERVER:.c=.o}
SRCS_SERVER = srcs/server.c

NAME_CLIENT = client
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
SRCS_CLIENT = srcs/client.c

all: ${NAME_SERVER} ${NAME_CLIENT}

deps: 
	$(MAKE) -C ./libs/libft/

${NAME_SERVER}: deps $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(NAME_SERVER)

$(NAME_CLIENT): deps $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBS) -o $(NAME_CLIENT)

clean:
	$(RM) -f $(OBJS_CLIENT) $(OBJS_SERVER)
	$(MAKE) clean -C libs/libft/

fclean: clean
	$(MAKE) fclean -C libs/libft/
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

