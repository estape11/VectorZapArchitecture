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

#include <Clock.hpp>

bit *Clock::Signal(void){
	return apSignal;

}

int Clock::Cycles(void) {
	return aCycles;
}

void Clock::Frequency(long frequency){
	aFrequency = frequency;

}

long Clock::Frequency(void){
	return aFrequency;

}

void Clock::Run(void){
	//printf("> Clock started \u26A1\n");
	aRun = true;
	long nanoSecs = 100000;
	if (aFrequency == 0) {
		nanoSecs = 999999999L;

	} else {
		nanoSecs = 1000000000/(2*aFrequency);

	}
	//printf("> %ldns\n", nanoSecs);
	//printf("> %ldHz\n", aFrequency);

	struct timespec sleepValue = {0};
	sleepValue.tv_nsec = nanoSecs;
	sleepValue.tv_sec = 0;

	//*apSignal = 1;
	
	while (aRun) {
		printf("tick - > %d\n", *apSignal);
		nanosleep(&sleepValue, NULL);
		if (*apSignal == 0) {
			*apSignal = 1;
			aCycles++;

		} else {
			*apSignal = 0;

		}
	}
	//printf("> Clock stopped\n");

}

void Clock::RunMutex(void) {
	nanosleep(&aSleepValue, NULL);

}

void Clock::RunKeyboard(void){
	//printf("> Clock started \u26A1\n");
	*apSignal = 0;
	aRun = true;
	//while (std::cin.get(c))	{
	while (fgetc(stdin)){
		if (!aRun){
			break;

		} // still running
		if (*apSignal == 0)	{
			*apSignal = 1;

		} else {
			*apSignal = 0;

		}
		// printf("tick - > %d\n", *apSignal);
	}
	//printf("> Clock stopped\n");

}

void Clock::Stop(void){
	aRun = false;

}

void Clock::Initialize(void){
	apSignal = (bit *) malloc(sizeof(bit));
	*apSignal = 1;

	aNanoSecs = 100000;
	if (aFrequency == 0) {
		aNanoSecs = 999999999L;

	} else {
		aNanoSecs = 500000000/(aFrequency);

	}
	aSleepValue = {0};
	aSleepValue.tv_nsec = aNanoSecs;
	aSleepValue.tv_sec = 0;

}