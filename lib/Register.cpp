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

void Register::Clk(char *signal){
	apClk = signal;

}

void Register::Enable(void){
	aEnable = true;

}

void Register::Disable(void){
	aEnable = false;

}

void Register::Run(void){
	aRun = true;
	while (aRun) {
		// Read data at clk = 0
		if (*apClk == 0 && aEnable == true) {
			// Copy the input value to data
			memcpy(apData, apInput, sizeof(char)*aWidth);
			
		} // else do nothing
	}

}

void Register::Stop(void){
	aRun = false;
}

char *Register::Data(void){
	return apData;

}

void Register::Input(char *input){
	apInput = input;

}

void Register::Initialize(void){
	apData = (char *) malloc(sizeof(char)*aWidth);

}