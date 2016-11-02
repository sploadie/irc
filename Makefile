# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2016/11/02 12:00:01 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 =			serveur
NAME2 =			client

CC =			clang -g

FLAGS =			-Wall -Werror -Wextra

HEADERS =		-I ./include -I $(LIBFT_DIR)

LIBRARIES =		-L$(LIBFT_DIR) -l$(LIBFT_NAME)

LIBFT_NAME =	ft

LIBFT =			$(LIBFT_DIR)lib$(LIBFT_NAME).a

LIBFT_DIR =		./libft/

SRC_DIR =		./src/

OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/

SHARED_FILES =	print get_dir strjoinfree readn palloc fd_limit
FILENAMES1 :=	server_main server_select server_init server_cmd channel
FILENAMES2 :=	client_main client_connect client_prompt client_send

OBJ_PATHS1 :=	$(addsuffix .o,$(SHARED_FILES) $(FILENAMES1))
OBJ_PATHS1 :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS1))

OBJ_PATHS2 :=	$(addsuffix .o,$(SHARED_FILES) $(FILENAMES2))
OBJ_PATHS2 :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS2))

OBJ_PATHS :=	$(addsuffix .o,$(SHARED_FILES) $(FILENAMES1) $(FILENAMES2))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

all: $(NAME1) $(NAME2)

$(NAME1): $(LIBFT) $(OBJ_PATHS1)
	$(CC) $(FLAGS) $(HEADERS) $(LIBRARIES) $(OBJ_PATHS1) -o $(NAME1)

$(NAME2): $(LIBFT) $(OBJ_PATHS2)
	$(CC) $(FLAGS) $(HEADERS) $(LIBRARIES) $(OBJ_PATHS2) -o $(NAME2)

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@/bin/mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

$(LIBFT):
	(cd $(LIBFT_DIR) && make)

clean:
	-/bin/rm -f $(OBJ_PATHS)
	/usr/bin/find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean: clean
	-/bin/rm -f  $(NAME1) $(NAME2)

re: fclean all
