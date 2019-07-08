NAME = ft_gkrellm

SRC = main.cpp \
		OSInfo.class.cpp \
		TextMode.cpp \
		GraphMode.cpp

HEADERS = IMonitorDisplay.hpp \
			IMonitorModule.hpp \
			OSInfo.class.hpp \
			TextMode.hpp \
			GraphMode.hpp

INCLUDES = -I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_ttf.framework/Headers/ \
			-F./frameworks

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
												-framework SDL2_ttf

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

#FLAGS = -Werror -Wall -Wextra

OBJ_DIR = ./obj

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADERS)
	clang++ -o $(NAME) $(OBJ) $(FRAMEWORKS) -lncurses

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	clang++ $(FLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
