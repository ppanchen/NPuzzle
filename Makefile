VPATH	=	sources

NAME = npuzzle

CC = g++

FLAGS = -std=c++14

LINKER_FLAGS = -lncurses

BIN_DIR = bin/

SRC = 	main.cpp \
		Board.cpp \
		Solver.cpp \
		Parser.cpp \
		Logger.cpp

BINS = $(addprefix $(BIN_DIR), $(SRC:.cpp=.o))

all: $(NAME)

$(BIN_DIR)%.o: %.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(BINS)
	$(CC) -o $(NAME) $(FLAGS) $(LINKER_FLAGS) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -d $(BIN_DIR)

re: fclean all