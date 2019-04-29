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

#include <string.h>
#include <stdlib.h>

#include <stdio.h>

class Register{
public:
	Register(){
		// Initial values
		aWidth = 0;
		apClk = NULL;
		aEnable = false;
		aRun = false;
		apData = NULL;
		apInput = NULL;

	}

	// Sets the width of the register
	// @author estape11
	// @params width
	// @return void
	void Width(int);

	// Gets the width of the register
	// @author estape11
	// @params void
	// @return width
	int Width(void);

	// Sets the clk signal
	// @author estape11
	// @params signal
	// @return void
	void Clk(char*);

	// Enable the register
	// @author estape11
	// @params void
	// @return void
	void Enable(void);

	// Disable the register
	// @author estape11
	// @params void
	// @return void
	void Disable(void);

	// Put to run the register
	// @author estape11
	// @params void
	// @return void
	void Run(void);

	// Stop the register execution
	// @author estape11
	// @params void
	// @return void
	void Stop(void);

	// Get the output of the register
	// @author estape11
	// @params void
	// @return void
	char *Data(void);
	
	// Sets the input of the register
	// @author estape11
	// @params void
	// @return void
	void Input(char *);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

private:
	int aWidth;
	char *apClk;
	bool aEnable;
	bool aRun;
	char *apData;
	char *apInput;

};