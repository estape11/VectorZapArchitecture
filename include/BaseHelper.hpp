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

#include <stdlib.h>
#include <math.h>

class BaseHelper{
public:
	BaseHelper(void){}

	// Converts a binary into decimal
	// @author estape11
	// @params binary, length
	// @return decimal
	int BinToDecimal(char *, int);

	// Converts a decimal into binary
	// @author estape11
	// @params decimal, length
	// @return binary
	char *DecimalToBin(int, int);
};