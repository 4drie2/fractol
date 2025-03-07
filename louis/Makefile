NAME 		= fractol

CC 			= cc
RM			= rm -f
CLONE 		= git clone --depth=1

CFLAGS 		= -Wall -Wextra -Werror -g -Ofast
CLINKS		= -ldl -lglfw -pthread -lm

MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= libft
LIBFT		= $(FT)/libft.a

SRC 		= fractol.c init_window.c mandelbrot.c palette.c hook.c Julia.c \
			  julia_mouse_track.c burning_ship.c tricorn.c parser.c\
			  parser_utils.c color_tech.c scroll_hook.c window_hook.c
OBJ 		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	@cmake $(MLX) -DDEBUG=1 -B $(MLX)
	$(MAKE) -C $(MLX)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)

$(MLX):
	$(CLONE) https://github.com/kodokaii/MLX42.git $(MLX)

$(FT):
	$(CLONE) https://github.com/Gpatrix/libft.git $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(MLX)" ]; then $(MAKE) clean -C $(MLX); fi
	@if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(LIBMLX)
	@$(RM) $(LIBFT)
	@$(RM) $(NAME)

clear: fclean
	@$(RM) -r $(MLX) 
	@$(RM) -r $(FT)

re: fclean all

.PHONY:		all clear clean fclean re facol

%.o: %.c
	@${CC} ${CFLAGS} -c -o $@ $< ${HEADERS}
