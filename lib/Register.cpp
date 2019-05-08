//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 28/04/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <Register.hpp>

void Register::Width(int width){
	aWidth = width;

}

int Register::Width(void){
	return aWidth;

}

// REMOVE
void Register::Ports(int ports) {
	aPorts = ports;

}

void Register::Clk(bit *pSignal){
	apClk = pSignal;

}

void Register::SetControlSignal(bit *pSignal){
	apEnable = pSignal;

}

void Register::Run(void){
	aRun = true;
	while (aRun) {
		if (*apClk == 1 && *apEnable == 1) {
			// memcpy(pTemp, apInput, aWidth);
			for (int i = 0; i < aPortsUsed; i++){
				memcpy(apTemp[i], apInput[i], BaseHelper::BinLength(apInput[i]));

			}
			//while (*apClk == 1);
			
		}

		if (*apClk == 0 && *apEnable == 1) {
			// memcpy(apData, pTemp, aWidth);
			for (int i = 0; i < aPorts; i++){
				memcpy(apData[i], apTemp[i], aWidth);

			}
			//while (*apClk == 0);

		}
		/**
		// Read data at clk = 1
		if (*apClk == 0 && *apEnable == 1) {
			memcpy(pTemp, apInput, aWidth);

		} else if (*apClk == 1 && *apEnable == 1) {
			// Copy the input value to data
			memcpy(apData, pTemp, aWidth);
			
		} // else do nothing
		**/
	}

}

void Register::RunMutex(void){
	if (!aClock && *apEnable == 1) {
		for (int i = 0; i < aPortsUsed; i++){
			memcpy(apTemp[i], apInput[i], BaseHelper::BinLength(apInput[i]));

		}
		
	}

	if (aClock && *apEnable == 1) {
		for (int i = 0; i < aPorts; i++){
			memcpy(apData[i], apTemp[i], aWidth);

		}

	}
	
	aClock = (aClock)? false : true;

}

void Register::Stop(void){
	aRun = false;
}

bit *Register::Output(int port){
	return apData[port];

}

//void Register::Input(bit *pInput){
//	apInput = pInput;

//}

void Register::Input(bit *pInput, int port){
	if (port < aPorts){
		apInput[port] = pInput;
		aPortsUsed++;

	}

}

void Register::Initialize(void){
	apInput = (bit **) malloc(sizeof(bit *)*aPorts);
	apData = (bit **) malloc(sizeof(bit *)*aPorts);
	apTemp = (bit **) malloc(sizeof(bit *)*aPorts);
	for (int i = 0; i < aPorts; i++){
		apData[i] = (bit *) malloc(sizeof(bit)*aWidth);
		apTemp[i] = (bit *) malloc(sizeof(bit)*aWidth);
		memset(apData[i], 0, aWidth);
		memset(apTemp[i], 0, aWidth);

	}
	// /memset(apData, 0, aWidth);

}