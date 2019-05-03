//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 03/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <Types.hpp>
#include <BaseHelper.hpp>
#include <stdlib.h>
#include <string.h>

class ScalarAlu {
public:
	ScalarAlu(void){
		apSelector = NULL;
		apOperA = NULL;
		apOperB = NULL;
		apResult = NULL;
		aWidth = 0;
		aRun = false;

	}

	// Sets the selector pointer
	// @author estape11
	// @params sel
	// @return void
	void Selector(bit *);

	// Sets the OperA pointer
	// @author estape11
	// @params operA
	// @return void
	void OperA(bit *);

	// Sets the OperA pointer
	// @author estape11
	// @params operB
	// @return void
	void OperB(bit *);

	// Sets the width of the ALU
	// @author estape11
	// @params width
	// @return void
	void Width(int);

	// Gets the result pointer
	// @author estape11
	// @params void
	// @return result
	bit *Result(void);

	// Sets the slector width
	// @author estape11
	// @params width
	// @return void
	void SelectorWidth(int);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

	// Starts the ALU
	// @author estape11
	// @params void
	// @return void
	void Run(void);

private:
	bit *apSelector;
	bit *apOperA;
	bit *apOperB;
	bit *apResult;
	int aWidth;
	int aSelectorWidth;
	bool aRun;

};