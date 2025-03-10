# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 19:09:36 by abidaux           #+#    #+#              #
#    Updated: 2025/03/07 19:54:34 by abidaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
ARCHIVE = push_swap.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAKE_LIB = ar -rcs

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_REPO = https://github.com/4drie2/libft.git

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(NAME) : $(ARCHIVE) $(LIBFT)
	$(CC) $< $(LIBFT) -o $@

$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $^

$(LIBFT) :
	@echo "Download libft from github..."
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	else \
		cd $(LIBFT_DIR) && git pull; \
	fi
	@echo "Compilation de la libft..."
	@$(MAKE) -C $(LIBFT_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

bonus :
	cd ../checker && make

clean :
	rm -f $(OBJS) $(ARCHIVE)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	fi

fclean : clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi
	cd ../checker && make fclean

re : fclean all

.PHONY : all clean fclean re
