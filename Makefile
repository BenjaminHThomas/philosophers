# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bento <bento@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:53:55 by bthomas           #+#    #+#              #
#    Updated: 2024/06/30 09:08:37 by bento            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCDIR	= src
OBJDIR	= objs
CFILES	= main.c \
		  validate_input.c \
		  init.c \
		  cleanup.c \
		  utils1.c \
		  utils2.c \
		  time_utils.c \
		  messages.c \
		  philo.c \
		  hangman.c

SRCS	= $(addprefix $(SRCDIR)/, $(CFILES))
OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -pthread -g3
INCS	= -I./include

all: $(OBJDIR) $(NAME)
	@echo "Making philo..."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing philo..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
