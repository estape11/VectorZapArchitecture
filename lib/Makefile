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

# Classes names
CLK=Clock
REG=Register
BASE=BaseHelper
SREGFILE=ScalarRegisterFile
SALU=ScalarAlu
INSTMEM=InstructionMemory
CC=g++
INCLUDE=../include
AR=ar
OPTNS=-Wall -std=c++11

all:$(CLK).o $(REG).o $(BASE).o $(SREGFILE).o $(SALU).o $(INSTMEM).o

$(CLK).o:$(CLK).cpp
		$(CC) $(OPTNS) -c $(CLK).cpp -o $(CLK).o -I$(INCLUDE)

$(REG).o:$(REG).cpp
		$(CC) $(OPTNS) -c $(REG).cpp -o $(REG).o -I$(INCLUDE)

$(BASE).o:$(BASE).cpp
		$(CC) $(OPTNS) -c $(BASE).cpp -o $(BASE).o -I$(INCLUDE)

$(SREGFILE).o:$(SREGFILE).cpp
		$(CC) $(OPTNS) -c $(SREGFILE).cpp -o $(SREGFILE).o -I$(INCLUDE)

$(SALU).o:$(SALU).cpp
		$(CC) $(OPTNS) -c $(SALU).cpp -o $(SALU).o -I$(INCLUDE)

$(INSTMEM).o:$(INSTMEM).cpp
		$(CC) $(OPTNS) -c $(INSTMEM).cpp -o $(INSTMEM).o -I$(INCLUDE)

clean:
		rm -f *.o 
		rm -f *.a
		
.PHONY:clean
