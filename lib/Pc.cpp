//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 06/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <Pc.hpp>

void Pc::Width(int width){
	aWidth = width;

}

void Pc::Clk(bit *pSignal){
	apClk = pSignal;

}

void Pc::SetControlSignal(bit *pSignal){
	apEnable = pSignal;

}

void Pc::Run(void){
	aRun = true;
	bool increment = false;
	while (aRun) {
		// Read data at clk = 0
		if (*apClk == 0 && *apEnable == 1) {
			// Copy the input value to data
			memcpy(apData, BaseHelper::DecimalToBin(aCounter, aWidth), sizeof(bit)*aWidth);
			if (!increment){
				aCounter++;
				increment = true;
				
			}
			//while(*apClk == 0);
		} else if (*apClk == 1 && *apEnable == 1) {
			increment = false;

		}
	}

}

void Pc::RunMutex(void) {
	if (aClock && *apEnable == 1) {
		// Copy the input value to data
		memcpy(apData, BaseHelper::DecimalToBin(aCounter, aWidth), aWidth);

	} 

	if (!aClock && *apEnable == 1) {
		aCounter++;

	}

	aClock = (aClock)? false : true;

}

void Pc::Stop(void){
	aRun = false;
}

bit *Pc::Data(void){
	return apData;

}

void Pc::Initialize(void){
	apData = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apData, 0, aWidth);
	
}