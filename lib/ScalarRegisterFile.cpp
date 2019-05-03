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

#include <ScalarRegisterFile.hpp>

void ScalarRegisterFile::DataIn(bit *pDataIn){
	apDataIn = pDataIn;
		
}

bit *ScalarRegisterFile::OutA(void){
	return apOutA;

}

bit *ScalarRegisterFile::OutB(void){
	return apOutB;

}

void ScalarRegisterFile::RegA(bit *pRegA){
	apRegA = pRegA;

}

void ScalarRegisterFile::RegB(bit *pRegB){
	apRegB = pRegB;

}

void ScalarRegisterFile::RegC(bit *pRegC){
	apRegC = pRegC;

}

void ScalarRegisterFile::SetControlSignals(bit *pEnableR, bit *pEnableW){
	apEnableR = pEnableR;
	apEnableW = pEnableW;

}

void ScalarRegisterFile::Clk(bit *pClk){
	apClk = pClk;

}

void ScalarRegisterFile::Width(int width){
	aWidth = width;

}

void ScalarRegisterFile::Length(int length){
	aLength = length;

}

void ScalarRegisterFile::Initialize(void){
	// Initialize the registers
	apData = (bit **) malloc(sizeof(bit *)*aLength);
	apOutA = (bit *) malloc(sizeof(bit)*aWidth);
	apOutB = (bit *) malloc(sizeof(bit)*aWidth);

	// Setup the registers
	for (int i = 0 ; i < aLength ; i++) {
		apData[i] = (bit *) malloc(sizeof(bit)*aWidth);
		memset(apData[i], 0, aWidth);

	}

}

void ScalarRegisterFile::Run(void){
	aRun = true;
	int indexA = 0;
	int indexB = 0;
	int indexC = 0;

	while (aRun) {
		if (*apClk == 0 && *apEnableW == 1) {
			indexC = BaseHelper::BinToDecimal(apRegC, aWidth);
			// Reg zero can be written
			if (indexC != 0 && indexC < pow(2, aLength)){
				// Saves the new data
				memcpy(apData[indexC], apDataIn, sizeof(bit)*aWidth);

			} // index out of bounds

		} // Do not write

		if (*apClk == 1 && *apEnableR == 1) {
			indexA = BaseHelper::BinToDecimal(apRegA, aWidth);
			indexB = BaseHelper::BinToDecimal(apRegB, aWidth);

			if (indexA < pow(2, aLength) && indexB < pow(2, aLength)){
				memcpy(apOutA, apData[indexA], sizeof(bit)*aWidth);
				memcpy(apOutB, apData[indexB], sizeof(bit)*aWidth);
				
			} // indexes out of bounds
			
		} // Do not read
	}

}