CC = g++
CFLAGS = -std=c++17 -Wall
OBJ = main.o Database.o QueryEngine.o
EXEC = main

# Rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.cpp Database.h QueryEngine.h
	$(CC) $(CFLAGS) -c main.cpp

Database.o: Database.cpp Database.h
	$(CC) $(CFLAGS) -c Database.cpp

QueryEngine.o: QueryEngine.cpp QueryEngine.h Database.h
	$(CC) $(CFLAGS) -c QueryEngine.cpp

clean:
	del /f $(OBJ) $(EXEC)

run: $(EXEC)
	$(EXEC)

.PHONY: all clean run
