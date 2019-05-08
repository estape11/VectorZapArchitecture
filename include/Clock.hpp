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

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <Types.hpp>

class Clock{
public:
	Clock(){
		// Initial values
		apSignal = NULL;
		aRun = false;
		aFrequency = 1;
		aCycles = 0;

	}

	// Gets the signal pointer
	// @author estape11
	// @params void
	// @return signal
	bit *Signal(void);

	// Gets the current number of cycles
	// @author estape11
	// @params void
	// @return cycles
	int Cycles(void);

	// Sets the frequency of the clock
	// @author estape11
	// @params frequency
	// @return void
	void Frequency(long);

	// Gets the frequency value
	// @author estape11
	// @params void
	// @return frequency
	long Frequency(void);

	// Put the clock to run
	// @author estape11
	// @params void
	// @return void
	void Run(void);

	void RunMutex(void);

	// Put the clock to run by keyboard (enter)
	// @author estape11
	// @params void
	// @return void
	void RunKeyboard(void);

	// Stops the clock
	// @author estape11
	// @params voids
	// @return void
	void Stop(void);

	// Initialize the signal
	// @author estape11
	// @params voids
	// @return void
	void Initialize(void);

private:
	char *apSignal;
	bool aRun;
	long aFrequency;
	int aCycles;
	long aNanoSecs;
	struct timespec aSleepValue;

};