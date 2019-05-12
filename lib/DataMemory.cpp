//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 10/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <DataMemory.hpp>

void DataMemory::InScalar(bit *pIn) {
	apInScalar = pIn;

}

void DataMemory::InVector(bit *pIn) {
	apInVector = pIn;

}

void DataMemory::Address(bit *pAddress) {
	apAddress = pAddress;

}

void DataMemory::SetControlSignals(bit *pEnableW, bit *pEnableR, bit *pInSel, bit * pDump) {
	apEnableW = pEnableW;
	apEnableR = pEnableR;
	apInSel = pInSel;
	apDump = pDump;

}

bit *DataMemory::Output(void) {
	return apOutput;

}

void DataMemory::Width(int width) {
	aWidth = width;

}

void DataMemory::Length(int length) {
	aLength = length;

}

void DataMemory::Initialize(void) {
	// Initialize the registers
	apData = (bit **) malloc(sizeof(bit *)*aLength);
	apOutput = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apOutput, 0, aWidth);

}

void DataMemory::SaveMemory(char *pFile) {
	std::ofstream memFile (pFile);
	for (int i = 0; i <aLength; i++ ){
		for (int j = aWidth-1; j >= 0; j--){
			memFile << (int) apData[i][j];

		}
		memFile << "\n";

	}
	memFile.close();

}

void DataMemory::LoadMemory(char *pFile) {
	std::string line;
	std::ifstream memFile (pFile);
	int index = 0;
	if (memFile.is_open()){
		while (getline(memFile,line)){
			if ( index < aLength){ // If there is space to fill
				apData[index] = BaseHelper::StringToBin(line, aWidth);
				index++;
			} else{ // No more space for more data
				break;

			}

		}
		memFile.close();
		
		// If the file was not enough to fill the memory
		for ( ; index < aLength ; index++){
			apData[index] = (bit *) malloc(sizeof(bit)*aWidth);
			memset(apData[index], 0, aWidth);
		}

	} else { // Case the file cannot be opened
		// Setup the cells of memory in zero
		for (int i = 0 ; i < aLength ; i++) {
			apData[i] = (bit *) malloc(sizeof(bit)*aWidth);
			memset(apData[i], 0, aWidth);

		}

	}

}

void DataMemory::Run(void) {
	// Access the memory
	if (aClock && *apEnableW == 1) {
		int address = BaseHelper::BinToDecimal(apAddress, aWidth);
		if (address < aLength){
			// Saves the new data
			if (*apInSel == 0){
				memcpy(apData[address], apInScalar, aWidth);

			} else {
				if (!aVectWritten) { // low case
					memcpy(apData[address], apInVector, aWidth);
					aVectWritten = true;

				} else { // high case
					memcpy(apData[address+1], apInVector, aWidth);
					aVectWritten = false;
				}

			}
			//printf(">> Written on %d\n", address );
		} // index out of bounds
	} // Do not write

	if (!aClock && *apEnableR == 1) {
		int address = BaseHelper::BinToDecimal(apAddress, aWidth);
		if (address < aLength){
			if (*apInSel == 0){
				memcpy(apOutput, apData[address], aWidth);

			} else {
				if (!aVectReaded) { // low case
					memcpy(apOutput, apData[address], aWidth);
					aVectReaded = true;

				} else { // high case
					memcpy(apOutput, apData[address+1], aWidth);
					aVectReaded = false;

				}
				//printf(">> Readed from %d\n", address );
			}

		} // indexes out of bounds
		
	} // Do not read

	if (*apEnableR == 0 && *apEnableW == 0) {
		if (*apInSel == 0){
			memcpy(apOutput, apAddress, aWidth);

		} else {
			memcpy(apOutput, apInVector, aWidth);
			
		}

	}

	if (*apDump == 1) {
		SaveMemory("ram.txt");
		
	}

	aClock = (aClock)? false : true;

}