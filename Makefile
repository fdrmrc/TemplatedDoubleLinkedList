EXE = exe.x
CXX = c++
CXXFLAGS = -g -std=c++14 -Wall -Wextra	

SRC= main.cpp
OBJ=$(SRC:.cpp=.o)
INC = include/Node.h  include/Iterator.h  include/List.h

VPATH = ../include

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

%.o: %.cpp ap_error.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation


format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
