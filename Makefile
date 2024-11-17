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

BONUS_NAME_SERVER = server_bonus
BONUS_OBJS_SERVER = ${BONUS_SRCS_SERVER:.c=.o}
BONUS_SRCS_SERVER = srcs/server_bonus.c

BONUS_NAME_CLIENT = client_bonus
BONUS_OBJS_CLIENT = ${BONUS_SRCS_CLIENT:.c=.o}
BONUS_SRCS_CLIENT = srcs/client_bonus.c

NAME_SERVER = server
OBJS_SERVER = ${SRCS_SERVER:.c=.o}
SRCS_SERVER = srcs/server.c

NAME_CLIENT = client
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
SRCS_CLIENT = srcs/client.c

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(BONUS_NAME_SERVER) $(BONUS_NAME_CLIENT)

deps: 
	$(MAKE) -C ./libs/libft/

$(BONUS_NAME_SERVER): deps $(BONUS_OBJS_SERVER)
	$(CC) $(CFLAGS) $(BONUS_OBJS_SERVER) $(LIBS) -o $(BONUS_NAME_SERVER)

$(BONUS_NAME_CLIENT): deps $(BONUS_OBJS_CLIENT)
	$(CC) $(CFLAGS) $(BONUS_OBJS_CLIENT) $(LIBS) -o $(BONUS_NAME_CLIENT)

${NAME_SERVER}: deps $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(NAME_SERVER)

$(NAME_CLIENT): deps $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBS) -o $(NAME_CLIENT)

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
	$(RM) $(BONUS_OBJS_CLIENT) $(BONUS_OBJS_SERVER)
	$(MAKE) clean -C libs/libft/

fclean: clean
	$(MAKE) fclean -C libs/libft/
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	$(RM) $(BONUS_NAME_CLIENT) $(BONUS_NAME_SERVER)

re: fclean all

