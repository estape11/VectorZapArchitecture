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

void ScalarAlu::ImmB(bit *pImmB){
	apImmB = pImmB;

}

void ScalarAlu::Width(int width){
	aWidth = width;
}

void ScalarAlu::SelectorOpB(bit * pSelOpB){
	apSelectorOpB = pSelOpB;

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
		selector = BaseHelper::BinToDecimal(apSelector, aSelectorWidth);
		dataOperA = BaseHelper::BinToDecimal(apOperA, aWidth);
		dataOperB = BaseHelper::BinToDecimal(apOperB, aWidth);

		switch (selector){
			// case 0 it's not operation
			case 0x0: // Add
				// CHECK ABOUT FLAGS
				//resultTemp = dataOperA + dataOperB;
				resultTemp = 9;
				break;

			case 0x1: // Subs
				//resultTemp = dataOperA - dataOperB;
				resultTemp = 19;
				break;

			case 0x2: // OR
				resultTemp = dataOperA | dataOperB;
				//printf(">>>>>> OPA = %d, OPB = %d, R = %d\n", dataOperA, dataOperB, resultTemp);
				break;

			case 0x3: // AND
				resultTemp = dataOperA & dataOperB; 
				//printf(">>>>>> OPA = %d, OPB = %d, R = %d\n", dataOperA, dataOperB, resultTemp);
				break;

			case 0x4: // XOR
				resultTemp = dataOperA ^ dataOperB;
				break;

			case 0x5: // Shift left
				resultTemp = dataOperA << dataOperB;
				break;

			case 0x6: // Shift Right
				resultTemp = dataOperA >> dataOperB;
				break;

			default:
				resultTemp = 0;
				break;

		}

		memcpy(apResult, BaseHelper::DecimalToBin(resultTemp, aWidth), sizeof(bit)*aWidth);
		
	}
}

void ScalarAlu::RunMutex(void){
	int selector = BaseHelper::BinToDecimal(apSelector, aSelectorWidth);
	int dataOperA = BaseHelper::BinToDecimal(apOperA, aWidth);
	int dataOperB = BaseHelper::BinToDecimal(apOperB, aWidth);
	int dataImmOperB = BaseHelper::BinToDecimal(apImmB, 11); // can be a parameter
	int resultTemp = 0;

	switch (selector){
		// case 0 it's not operation
		case 0x0: // Add
			// CHECK ABOUT FLAGS
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA + dataOperB;

			} else {
				resultTemp = dataOperA + dataImmOperB;
				
			}
			break;

		case 0x1: // Subs
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA - dataOperB;

			} else {
				resultTemp = dataOperA - dataImmOperB;

			}

			break;

		case 0x2: // OR
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA | dataOperB;

			} else {
				resultTemp = dataOperA | dataImmOperB;

			}
			break;

		case 0x3: // AND
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA & dataOperB; 

			} else {
				resultTemp = dataOperA & dataImmOperB;

			}
			break;

		case 0x4: // XOR
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA ^ dataOperB;

			} else {
				resultTemp = dataOperA ^ dataImmOperB;

			}
			break;

		case 0x5: // Shift left
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA << dataOperB;

			} else {
				resultTemp = dataOperA << dataImmOperB;

			}
			break;

		case 0x6: // Shift Right
			if (*apSelectorOpB == 0){
				resultTemp = dataOperA >> dataOperB;

			} else {
				resultTemp = dataOperA >> dataImmOperB;

			}
			break;

		case 0x9: // OperA
			resultTemp = dataOperA;
			break;

		case 0xA: // OperB
			if (*apSelectorOpB == 0){
				resultTemp = dataOperB;
			} else {
				resultTemp = dataImmOperB;
				
			}
			break;

		case 0xB: // Circular Shift left
			if (*apSelectorOpB == 0){
				memcpy(apResult, 
					BaseHelper::CircularShiftLeft(
						apOperA, aWidth, dataOperB), aWidth);

			} else {
				memcpy(apResult, 
					BaseHelper::CircularShiftLeft(
						apOperA, aWidth, dataImmOperB), aWidth);

			}
			if (aWidth == 1 ){
				printf(">> Lane In A ");
				BaseHelper::PrintBin(apOperA, aWidth);
				printf(">> Lane In B ");
				BaseHelper::PrintBin(apOperB, aWidth);
				printf(">> Immediate ");
				BaseHelper::PrintBin(apSelectorOpB, 1);
				printf(">>> Lane Out ");
				BaseHelper::PrintBin(apResult, aWidth);
			}
			return;

		case 0xC: // Circular Shift Right
			if (*apSelectorOpB == 0){
				memcpy(apResult, 
					BaseHelper::CircularShiftRight(
						apOperA, aWidth, dataOperB), aWidth);

			} else {
				memcpy(apResult, 
					BaseHelper::CircularShiftRight(
						apOperA, aWidth, dataImmOperB), aWidth);

			}

			return;

		default:
			resultTemp = 0;
			break;

	}
	memcpy(apResult, BaseHelper::DecimalToBin(resultTemp, aWidth), sizeof(bit)*aWidth);

}