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

#include <string.h>
#include <stdlib.h>
#include <Types.hpp>
#include <BaseHelper.hpp>

class Pc{
public:
	Pc(){
		// Initial values
		aWidth = 0;
		apClk = NULL;
		apEnable = NULL;
		aRun = false;
		apData = NULL;
		aCounter = 0;
		aClock = false;

	}

	// Sets the width of the register
	// @author estape11
	// @params width
	// @return void
	void Width(int);

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
	// @params void
	// @return void
	bit *Data(void);
	
	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

private:
	int aWidth;
	bit *apClk;
	bool aClock;
	bit *apEnable;
	bool aRun;
	bit *apData;
	int aCounter;

};