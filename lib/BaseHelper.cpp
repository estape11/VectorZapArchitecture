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

#include <BaseHelper.hpp>

int BaseHelper::BinToDecimal(char * pBinary, int length){
	int decimal = 0;
	for (int i = length-1 ; i >= 0  ; i--){
		decimal += pBinary[i]*pow(2,i);

	}
	return decimal;

}

char *BaseHelper::DecimalToBin(int decimal, int length){
	char *pBinary = (char *) malloc(sizeof(char)*length);
	int decimalTemp = decimal;
	for (int i = 0 ; i < length ; i++){
		pBinary[i] = decimalTemp%2;
		decimalTemp /= 2;

	}
	return pBinary;

}