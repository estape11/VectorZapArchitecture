//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 05/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <VectorRegisterFile.hpp>

void VectorRegisterFile::DataIn(bit *pDataIn){
	apDataIn = pDataIn;
		
}

bit *VectorRegisterFile::OutA(void){
	return apOutA;

}

bit *VectorRegisterFile::OutB(void){
	return apOutB;

}

void VectorRegisterFile::RegA(bit *pRegA){
	apRegA = pRegA;

}

void VectorRegisterFile::RegB(bit *pRegB){
	apRegB = pRegB;

}

void VectorRegisterFile::RegC(bit *pRegC){
	apRegC = pRegC;

}

void VectorRegisterFile::SetControlSignals(bit *pEnableR, bit *pEnableW, bit *pDump){
	apEnableR = pEnableR;
	apEnableW = pEnableW;
	apDump = pDump;

}

void VectorRegisterFile::Clk(bit *pClk){
	apClk = pClk;

}

void VectorRegisterFile::Width(int width){
	aWidth = width;

}

void VectorRegisterFile::Length(int length){
	aLength = length;

}

void VectorRegisterFile::AddressWidth(int width){
	aAddressWidth = width;

}

void VectorRegisterFile::Initialize(void){
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

void VectorRegisterFile::SaveMemory(char *pFile){
	std::ofstream memFile (pFile);
	for (int i = 0; i <aLength; i++ ){
		for (int j = aWidth-1; j >= 0; j--){
			memFile << (int) apData[i][j];

		}
		memFile << "\n";

	}
	memFile.close();

}

void VectorRegisterFile::Run(void){
	aRun = true;
	int indexA = 0;
	int indexB = 0;
	int indexC = 0;

	while (aRun) {
		if (*apClk == 0 && *apEnableW == 1) {
			indexC = BaseHelper::BinToDecimal(apRegC, aAddressWidth);
			// Reg zero cannot be written
			if (indexC != 0 && indexC < aLength){
				// Saves the new Data
				if (!aWriteStatus) { // Case Low
					memcpy(apData[indexC], apDataIn, aWidth/2);
					aWriteStatus = true; // To write the High part
					while (*apClk == 0); // Waits the clock to change

				} else { // Case High
					memcpy(apData[indexC]+aWidth/2, apDataIn, aWidth/2);
					aWriteStatus = false; // Restore the status
					while (*apClk == 0); // Waits the clock to change

				}

			} // index out of bounds

		} // Do not write

		if (*apClk == 1 && *apEnableR == 1) {
			indexA = BaseHelper::BinToDecimal(apRegA, aAddressWidth);
			indexB = BaseHelper::BinToDecimal(apRegB, aAddressWidth);

			if (indexA < aLength && indexB < aLength){
				if (!aReadStatus) { // Case low
					memcpy(apOutA, apData[indexA], aWidth/2);
					memcpy(apOutB, apData[indexB], aWidth/2);
					aReadStatus = true; // To read the High part
					while (*apClk == 1); // Waits the clock to change

				} else { // Case High
					memcpy(apOutA, apData[indexA]+aWidth/2, aWidth/2);
					memcpy(apOutB, apData[indexB]+aWidth/2, aWidth/2);
					aReadStatus = false; // Restore the status
					while (*apClk == 1); // Waits the clock to change

				}
				
			} // indexes out of bounds
			
		} // Do not read
	}

}

void VectorRegisterFile::RunMutex(void){
	if (aClock && *apEnableW == 1) {
		int indexC = BaseHelper::BinToDecimal(apRegC, aAddressWidth);
		// Reg zero cannot be written
		if (indexC != 0 && indexC < aLength){
			// Saves the new Data
			if (!aWriteStatus) { // Case Low
				memcpy(apData[indexC], apDataIn, aWidth/2);
				aWriteStatus = true; // To write the High part

			} else { // Case High
				memcpy(apData[indexC]+aWidth/2, apDataIn, aWidth/2);
				aWriteStatus = false; // Restore the status

			}
			//printf(">> Data Writted > ");
			//BaseHelper::PrintBin(apDataIn, aWidth/2);
			//printf(">> Index %d\n", indexC);

		} // index out of bounds

	} // Do not write

	if (!aClock && *apEnableR == 1) {
		int indexA = BaseHelper::BinToDecimal(apRegA, aAddressWidth);
		int indexB = BaseHelper::BinToDecimal(apRegB, aAddressWidth);

		if (indexA < aLength && indexB < aLength){
			if (!aReadStatus) { // Case low
				memcpy(apOutA, apData[indexA], aWidth/2);
				memcpy(apOutB, apData[indexB], aWidth/2);
				aReadStatus = true; // To read the High part

			} else { // Case High
				memcpy(apOutA, apData[indexA]+aWidth/2, aWidth/2);
				memcpy(apOutB, apData[indexB]+aWidth/2, aWidth/2);
				aReadStatus = false; // Restore the status

			}

		} // indexes out of bounds
		//printf("Reading > \n");
		//BaseHelper::PrintBin(apOutA, aWidth/2);
		//BaseHelper::PrintBin(apOutB, aWidth/2);
		
	} // Do not read

	if (*apDump == 1) {
		SaveMemory("/home/estape/vector.txt");
		
	}

	aClock = (aClock)? false : true;
}