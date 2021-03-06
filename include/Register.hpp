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
#include <Types.hpp>
#include <stdio.h>
#include <BaseHelper.hpp>

class Register{
public:
	Register(){
		// Initial values
		aWidth = 0;
		apClk = NULL;
		apEnable = NULL;
		aRun = false;
		apData = NULL;
		apInput = NULL;
		apTemp = NULL;
		aPorts = 0;
		aPortsUsed = 0;
		aClock = false;

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

	// Sets t
	// @author estape11
	// @params void
	// @return width
	void Ports(int);

	// Sets the clk signal
	// @author estape11
	// @params signal
	// @return void
	void Clk(bit *);

	// Sets the control signal
	// @author estape11
	// @params signal
	// @return void
	void SetControlSignal(bit *);

	// Put to run the register
	// @author estape11
	// @params void
	// @return void
	void Run(void);

	void RunMutex(void);

	// Stop the register execution
	// @author estape11
	// @params void
	// @return void
	void Stop(void);

	// Get the output of the register
	// @author estape11
	// @params port
	// @return void
	bit *Output(int);
	
	// Sets the input of the register
	// @author estape11
	// @params void
	// @return void
	//void Input(bit *);

	void Input(bit *, int);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

private:
	int aWidth;
	bit *apClk;
	bit *apEnable;
	bool aRun;
	bit **apData;
	bit **apInput;
	int aPorts;
	bit **apTemp;
	int aPortsUsed;
	bool aClock;

};