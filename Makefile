NAME = packparsley

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/

LIB =


SRC_FILES =		main.cpp \
				PacketParser.cpp \
				Exceptions.cpp \
				AList.cpp

HEADERS = 		$(INC_DIR)PacketParser.hpp \
				$(INC_DIR)Exceptions.hpp \
				$(INC_DIR)AList.hpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

CC = g++ -std=c++11
CFLAGS = -Wall -Werror -Wextra
INC = 	-I $(INC_DIR)

C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INC) -o $(NAME)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@


$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all