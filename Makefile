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

all: src lib

src: lib
		$(MAKE) -C src
lib:
		$(MAKE) -C lib

clean:
		$(MAKE) -C src clean
		$(MAKE) -C lib clean
		clear

.PHONY: src lib clean