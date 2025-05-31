CC = g++

CFLAGS = -Wall -g -W -pedantic -std=c++23

TARGET = main

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)

clean: all
	rm -rf $(TARGET)
