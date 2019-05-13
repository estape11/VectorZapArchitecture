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

#include <Types.hpp>
#include <BaseHelper.hpp>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

class InstructionMemory{
public:
	InstructionMemory(void) {
		aWidth = 0;
		aLength = 0;
		aRun = false;
		apData = NULL;
		apInput = NULL;
		apOutput = NULL;
	}

	void Width(int);
	void Length(int);
	void Input(bit *);
	bit *Output(void);
	void Initialize(void);
	void Run(void);
	void RunMutex(void);
	void LoadMemory(std::string);

private:
	int aWidth;
	int aLength;
	bool aRun;
	bit **apData;
	bit *apInput;
	bit *apOutput;

};