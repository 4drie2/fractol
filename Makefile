# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 19:09:36 by abidaux           #+#    #+#              #
#    Updated: 2025/03/11 17:33:15 by abidaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

FULL_CFLAGS = $(CFLAGS) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd -I$(LIBFT_DIR)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Téléchargement de la libft...$(RESET)"
	@git clone https://github.com/4drie2/libft.git $(LIBFT_DIR) 2>/dev/null || (cd $(LIBFT_DIR) && git pull)
	@echo "$(BLUE)Compilation de la libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compilée avec succès !$(RESET)"
NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I ~/my_libs/minilibx/ -L ~/my_libs/minilibx/ -lmlx -lX11 -lXext -lbsd -Lminilibx-linux

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Téléchargement de la libft...$(RESET)"
	@git clone https://github.com/4drie2/libft.git $(LIBFT_DIR) 2>/dev/null || (cd $(LIBFT_DIR) && git pull)
	@echo "$(BLUE)Compilation de la libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compilée avec succès !$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)Création de l'exécutable $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(CFLAGS)
	@echo "$(GREEN)Compilation de $(NAME) terminée avec succès !$(RESET)"

clean:
	@echo "$(RED)Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "$(RED)Suppression du dossier libft...$(RESET)"; \
		rm -rf $(LIBFT_DIR); \
	fi
	@echo "$(GREEN)Nettoyage complet terminé !$(RESET)"

re: fclean all

.PHONY: all clean fclean re

$(MLX):
	@echo "$(BLUE)Téléchargement de la minilibx...$(RESET)"
	@git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR) 2>/dev/null || (cd $(MLX_DIR) && git pull)
	@echo "$(BLUE)Compilation de la minilibx...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)Minilibx compilée avec succès !$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(FULL_CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)Création de l'exécutable $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd
	@echo "$(GREEN)Compilation de $(NAME) terminée avec succès !$(RESET)"

clean:
	@echo "$(RED)Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean 2>/dev/null || true
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "$(RED)Suppression du dossier libft...$(RESET)"; \
		rm -rf $(LIBFT_DIR); \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "$(RED)Suppression du dossier minilibx...$(RESET)"; \
		rm -rf $(MLX_DIR); \
	fi
	@echo "$(GREEN)Nettoyage complet terminé !$(RESET)"

re: fclean all

.PHONY: all clean fclean re
