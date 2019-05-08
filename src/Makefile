#************************************************************
#
#	Instituto Tecnológico de Costa Rica
#	Computer Engineering
#
#	Programmer: Esteban Agüero Pérez (estape11)
#	Version: 1.0
#	Last Update: 28/04/2019
#
#	Computer Architecture II
#	Professor. Jeferson González Gómez
#
#************************************************************

CC=g++
FLAGS=
APP=main
LINKER_FLAGS=-pthread
LIBS=../lib
OUT=../bin
OPTNS=-w -std=c++11
INCLUDE=../include

all:setup $(APP)

setup:
		mkdir -p $(OUT)

$(APP).o:$(APP).cpp
		$(CC) $(OPTNS) -c $(APP).cpp -o $(APP).o -I$(INCLUDE)

# Linking with the libraries and binary generation
$(APP):$(APP).o setup
		$(CC) -o $(OUT)/$(APP) $(APP).o $(LIBS)/*.o -L$(LIBS) $(LINKER_FLAGS)

clean:
		rm -rf $(OUT)
		rm -f *.o

.PHONY:clean setup
