# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:53:55 by bthomas           #+#    #+#              #
#    Updated: 2024/06/18 15:03:09 by bthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCDIR	= srcs
OBJDIR	= objs
CFILES	= main.c
SRCS	= $(addprefix $(SRCDIR)/, $(CFILES))
OBJS	= $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
INCS	= -I./includes

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
	@rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
