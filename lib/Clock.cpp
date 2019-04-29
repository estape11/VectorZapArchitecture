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

char *Clock::Signal(void){
	return apSignal;

}

void Clock::Frequency(long frequency){
	aFrequency = frequency;

}

long Clock::Frequency(void){
	return aFrequency;

}

void Clock::Run(void){
	printf("> Clock started \u26A1\n");
	aRun = true;
	long nanoSecs;
	if (aFrequency == 1) {
		nanoSecs = 999999999L;

	} else {
		nanoSecs = 1000000000/aFrequency;

	}
	printf("> %ldns\n", nanoSecs);
	printf("> %ldHz\n", aFrequency);

	struct timespec sleepValue = {0};
	sleepValue.tv_nsec = nanoSecs;
	sleepValue.tv_sec = 0;

	*apSignal = 1;
	
	while (aRun) {
		nanosleep(&sleepValue, NULL);
		if (*apSignal == 0) {
			*apSignal = 1;

		} else {
			*apSignal = 0;

		}
		printf("tick - > %d\n", *apSignal);
	}
	printf("> Clock stopped\n");

}

void Clock::RunKeyboard(void){
	printf("> Clock started \u26A1\n");
	*apSignal = 1;
	char c = '\0';
	aRun = true;
	while (std::cin.get(c))	{
		if (!aRun){
			break;

		} // still running
		if (*apSignal == 0)	{
			*apSignal = 1;

		} else {
			*apSignal = 0;

		}
		printf("tick - > %d\n", *apSignal);
	}

	printf("> Clock stopped\n");

}

void Clock::Stop(void){
	aRun = false;

}

void Clock::Initialize(void){
	apSignal = (char *) malloc(sizeof(char));
	*apSignal = 0;
}