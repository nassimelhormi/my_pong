NAME		=	pong

SRC		=	main.c \
			list_player.c \
			player.c \
			sdl.c \
			server.c \
			client.c

OBJ		=	$(SRC:.c=.o)

INC_DIR 	=	~/System/Library/Frameworks
SDL_PATH	=	$(INC_DIR)/SDL2.framework/Headers
SDL_IMAGE_PATH 	=	$(INC_DIR)/SDL2_image.framework/Headers
SDL_TTF_PATH	= 	$(INC_DIR)/SDL2_ttf.framework/Headers
CFLAGS		=	-W -Wall -Werror -I $(INC_DIR)
SDL_FLAGS	=	-I $(SDL_PATH) -framework SDL2
SDL_IMAGE_FLAGS =	-I $(SDL_IMAGE_PATH) -framework SDL2_image
SDL_TTF_FLAGS	=	-I $(SDL_TTF_PATH) -framework SDL2_ttf
CC		=	gcc

rm		=	rm -f

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(SDL_FLAGS) $(SDL_IMAGE_FLAGS) $(SDL_TTF_FLAGS)
clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
