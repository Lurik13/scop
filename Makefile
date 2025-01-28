CC = c++
DEBUGGING_FLAGS += -Wall -Wextra -Werror -g
OPENGL_FLAGS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
FLAGS += $(DEBUGGING_FLAGS) $(OPENGL_FLAGS)
INCLUDE = -I./include -I./libs


# ----------------------------- Sources ----------------------------- #

NAME = scop
FILES = 

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))


# ------------------------------ Rules ------------------------------ #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ $(FLAGS) $(INCLUDE) libs/glad/glad.c
	@echo "\r\033[K\033[38;2;0;170;0;1mSuccessfully compiled to \033[38;2;255;145;5;3m./$(NAME)\033[0m\033[38;2;0;170;0;1m!\033[0m"

%.o: %.cpp
	@echo -n "\r\033[38;2;0;170;0m$(CC) -o $@ -c $< $(FLAGS)"
	@$(CC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJS)
	@echo "\r\033[K\033[38;2;170;0;0;1mAll object files have been successfully deleted.\033[0m"

fclean:
	@rm -rf $(OBJS)
	@rm -rf $(NAME)
	@echo "\r\033[K\033[38;2;170;0;0;1mAll object files and \033[38;2;255;145;5;3m./$(NAME)\033[0m\033[38;2;170;0;0;1m have been successfully deleted.\033[0m"

re: fclean all

code: fclean all clean

.PHONY: all clean fclean re



# $@ : produit (ou but) de la règle 
# $< : nom de la première dépendance (ou source) 
# $? : toutes les dépendances plus récentes que le but 
# $^ : toutes les dépendances 
# $+ : idem mais chaque dépendance apparait autant de fois qu'elle
#      est citée et l'ordre d'apparition est conservé