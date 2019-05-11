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

#include <Types.hpp>
#include <BaseHelper.hpp>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

class DataMemory{
public:
	DataMemory(void) {
		aWidth = 0;
		aLength = 0;
		apData = NULL;
		apAddress = NULL;
		apInVector = NULL;
		apInScalar = NULL;
		apOutput = NULL;
		apEnableR = NULL;
		apEnableW = NULL;
		apInSel = NULL;
		aClock = false;
		aVectReaded = false;
		aVectWritten = false;
		apDump = NULL;

	}

	// Sets the scalar input
	// @author estape11
	// @params binIn
	// @return void
	void InScalar(bit *);

	// Sets the vector input
	// @author estape11
	// @params binIn
	// @return void
	void InVector(bit *);

	// Sets the address input
	// @author estape11
	// @params binIn
	// @return void
	void Address(bit *);

	// Sets the scalar input
	// @author estape11
	// @params enableW, enableR, inSel, dump
	// @return void
	void SetControlSignals(bit *, bit *, bit *, bit *);

	// Gets the output result
	// @author estape11
	// @params void
	// @return binary
	bit *Output(void);

	// Sets the cell width
	// @author estape11
	// @params width
	// @return void
	void Width(int);

	// Sets the memory length
	// @author estape11
	// @params length
	// @return void
	void Length(int);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

	// Saves the memory in a file
	// @author estape11
	// @params file
	// @return void
	void SaveMemory(char *);

	// Load file to memory
	// @author estape11
	// @params file
	// @return void
	void LoadMemory(char *);

	// Run the memory
	// @author estape11
	// @params void
	// @return void
	void Run(void);


private:
	int aWidth;
	int aLength;
	bit **apData;

	bit *apAddress;
	bit *apInVector;
	bit *apInScalar;
	bit *apOutput;

	bit *apEnableR;
	bit *apEnableW;
	bit *apInSel;
	bool aClock;

	bool aVectReaded;
	bool aVectWritten;

	bit *apDump;

};