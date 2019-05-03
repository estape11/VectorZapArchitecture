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

int BaseHelper::BinToDecimal(bit * pBinary, int length){
	int decimal = 0;
	for (int i = length-1 ; i >= 0  ; i--){
		decimal += pBinary[i]*pow(2,i);

	}
	return decimal;

}

bit *BaseHelper::DecimalToBin(int decimal, int length){
	bit *pBinary = (bit *) malloc(sizeof(bit)*length);
	int decimalTemp = decimal;
	for (int i = 0 ; i < length ; i++){
		pBinary[i] = decimalTemp%2;
		decimalTemp /= 2;

	}
	return pBinary;

}

void BaseHelper::PrintBin(bit *data, int lenght){
	for (int i = lenght-1; i >= 0  ; i--){
		printf("%d", data[i]);

	}
	printf("\n");
	
}
