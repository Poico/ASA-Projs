CC = g++
CFLAGS = -Wall -o -O3 -std=c++11

SRC = grafos_covid.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = grafos_covid

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
