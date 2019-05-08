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

void ScalarRegisterFile::AddressWidth(int width){
	aAddressWidth = width;

}

void ScalarRegisterFile::SaveMemory(char *pFile){
	std::ofstream memFile (pFile);
	for (int i = 0; i <aLength; i++ ){
		for (int j = aWidth; j >= 0; j--){
			memFile << (int) apData[i][j];

		}
		memFile << "\n";

	}
	memFile.close();

}

void ScalarRegisterFile::Initialize(void){
	// Initialize the registers
	apData = (bit **) malloc(sizeof(bit *)*aLength);
	apOutA = (bit *) malloc(sizeof(bit)*aWidth);
	apOutB = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apOutA, 0, aWidth);
	memset(apOutB, 0, aWidth);

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
			indexC = BaseHelper::BinToDecimal(apRegC, aAddressWidth);			
			// Reg zero cannot be written
			if (indexC != 0 && indexC < aLength){
				// Saves the new data
				memcpy(apData[indexC], apDataIn, aWidth);
				SaveMemory("/home/estape/t.txt");

			} // index out of bounds

		} // Do not write

		if (*apClk == 1 && *apEnableR == 1) {
			indexA = BaseHelper::BinToDecimal(apRegA, aAddressWidth);
			indexB = BaseHelper::BinToDecimal(apRegB, aAddressWidth);

			if (indexA < aLength && indexB < aLength){
				memcpy(apOutA, apData[indexA], aWidth);
				memcpy(apOutB, apData[indexB], aWidth);
				
			} // indexes out of bounds
			
		} // Do not read
	}

}

void ScalarRegisterFile::RunMutex(void){
	if (aClock && *apEnableW == 1) {
		int indexC = BaseHelper::BinToDecimal(apRegC, aAddressWidth);			
		// Reg zero cannot be written
		if (indexC != 0 && indexC < aLength){
			// Saves the new data
			memcpy(apData[indexC], apDataIn, aWidth);
			SaveMemory("/home/estape/t.txt");

		} // index out of bounds

	} // Do not write

	if (!aClock && *apEnableR == 1) {
		int indexA = BaseHelper::BinToDecimal(apRegA, aAddressWidth);
		int indexB = BaseHelper::BinToDecimal(apRegB, aAddressWidth);

		if (indexA < aLength && indexB < aLength){
			memcpy(apOutA, apData[indexA], aWidth);
			memcpy(apOutB, apData[indexB], aWidth);
			
		} // indexes out of bounds
		
	} // Do not read

	aClock = (aClock)? false : true;

}