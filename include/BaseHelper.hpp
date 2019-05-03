//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 29/04/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#ifndef BASEHELPER
#define BASEHELPER

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Types.hpp>

class BaseHelper{
public:
	BaseHelper(void){}

	// Converts a binary into decimal
	// @author estape11
	// @params binary, length
	// @return decimal
	static int BinToDecimal(bit *, int);

	// Converts a decimal into binary
	// @author estape11
	// @params decimal, length
	// @return binary
	static char *DecimalToBin(int, int);

	// Prints a binary value
	// @author estape11
	// @params binary, length
	// @return void
	static void PrintBin(bit *, int);
};

#endif