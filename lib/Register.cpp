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

void Register::Clk(bit *pSignal){
	apClk = pSignal;

}

void Register::SetControlSignal(bit *pSignal){
	apEnable = pSignal;

}

void Register::Run(void){
	aRun = true;
	while (aRun) {
		// Read data at clk = 0
		if (*apClk == 0 && *apEnable == 1) {
			// Copy the input value to data
			memcpy(apData, apInput, sizeof(bit)*aWidth);
			
		} // else do nothing
	}

}

void Register::Stop(void){
	aRun = false;
}

bit *Register::Data(void){
	return apData;

}

void Register::Input(bit *pInput){
	apInput = pInput;

}

void Register::Initialize(void){
	apData = (bit *) malloc(sizeof(bit)*aWidth);

}