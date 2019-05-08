//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 04/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <InstructionMemory.hpp>

void InstructionMemory::Width(int width){
	aWidth = width;

}

void InstructionMemory::Length(int length){
	aLength = length;

}

void InstructionMemory::Input(bit *pInput){
	apInput = pInput;

}

bit *InstructionMemory::Output(void){
	return apOutput;

}

void InstructionMemory::Initialize(void){
	// Initialize the registers
	apData = (bit **) malloc(sizeof(bit *)*aLength);
	apOutput = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apOutput, 0, aWidth);

}

void InstructionMemory::Run(void){
	aRun = true;
	int index = 0;

	while (aRun){
		index = BaseHelper::BinToDecimal(apInput, aWidth);

		if (index < aLength){
			memcpy(apOutput, apData[index], aWidth);
			//printf(">> %d\n", index);
			//BaseHelper::PrintBin(apOutput, aWidth);
			
		} // indexes out of bounds

	}
}

void InstructionMemory::RunMutex(void){
	int index = BaseHelper::BinToDecimal(apInput, aWidth);

	if (index < aLength){
		memcpy(apOutput, apData[index], aWidth);
		
	} // indexes out of bounds
}

void InstructionMemory::LoadMemory(char *pFile){
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
