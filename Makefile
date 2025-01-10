all:run 
CC=g++
CFLAGS=-O1 -Wall -std=c++17 -Wno-missing-braces -I./include/ -L ./lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
TARGET=main.exe
SRC=src/main.cpp 
DEPENDS = src/header.hpp
$(TARGET): $(SRC) $(DEPENDS) Makefile
	$(CC) $< -o $@ $(CFLAGS)
build: $(TARGET)
run: build
	./$(TARGET)

