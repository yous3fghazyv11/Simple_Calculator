CC = g++

CFLAGS = -Wall -g -W -pedantic

TARGET = main

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp

run: all
	./$(TARGET)
