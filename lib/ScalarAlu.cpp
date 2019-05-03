//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 03/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <ScalarAlu.hpp>

void ScalarAlu::Selector(bit *pSel){
	apSelector = pSel;

}

void ScalarAlu::OperA(bit *pOperA){
	apOperA = pOperA;

}

void ScalarAlu::OperB(bit *pOperB){
	apOperB = pOperB;

}

void ScalarAlu::Width(int width){
	aWidth = width;
}

bit *ScalarAlu::Result(void){
	return apResult;

}

void ScalarAlu::SelectorWidth(int width){
	aSelectorWidth = width;
}

void ScalarAlu::Initialize(void){
	apResult = (bit *) malloc(sizeof(bit)*aWidth);

}

void ScalarAlu::Run(void){
	aRun = true;
	int selector = 0;
	int dataOperA = 0;
	int dataOperB = 0;
	int resultTemp = 0;
	while (aRun) {
		selector = BaseHelper::BinToDecimal(apSelector, aWidth);
		dataOperA = BaseHelper::BinToDecimal(apOperA, aWidth);
		dataOperB = BaseHelper::BinToDecimal(apOperB, aWidth);

		switch (selector){
			// case 0 it's not operation
			case 0x1: // Add
				// CHECK ABOUT FLAGS
				resultTemp = dataOperA + dataOperB;
				break;

			case 0x2: // Subs
				resultTemp = dataOperA - dataOperB;
				break;

			case 0x3: // OR
				resultTemp = dataOperA | dataOperB;
				break;

			case 0x4: // AND
				resultTemp = dataOperA & dataOperB;
				break;

			case 0x5: // XOR
				resultTemp = dataOperA ^ dataOperB;
				break;

			case 0x6: // Shift left
				resultTemp = dataOperA << dataOperB;
				break;

			case 0x7: // Shift Right
				resultTemp = dataOperA >> dataOperB;
				break;

			default:
				resultTemp = 0;
				break;

		}

		memcpy(apResult, BaseHelper::DecimalToBin(resultTemp, aWidth), sizeof(bit)*aWidth);
		
	}
}