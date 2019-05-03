#include <Clock.hpp>
#include <Register.hpp>
#include <ScalarRegisterFile.hpp>
#include <Types.hpp>

#include <pthread.h>
#include <string.h>
#include <math.h>

// to decimal
void PrintData(char * data, int lenght){
	int temp = 0;
	for (int i = lenght-1; i >= 0  ; i--){
		printf("%d", data[i]);
		temp+=data[i]*pow(2,i);
	}
	printf("\n");
	//printf("-- %d\n", temp);
}

Clock clk;
Register reg;
ScalarRegisterFile RegisterBank;

void* startRegisterBank(void* args){
	RegisterBank.Run();
	pthread_exit(NULL);

}

void* startRegister(void* args){
	reg.Enable();
	reg.Run();
	pthread_exit(NULL);

}
void* startALU(void* args){
	clk.Frequency(1);
	//clk.Signal((char*)args);
	clk.RunKeyboard();
	pthread_exit(NULL);
}

void* startClock(void* args){
	clk.Frequency(1);
	//clk.Signal((char*)args);
	clk.Run();
	pthread_exit(NULL);
}

int main(int argc, const char* argv[]){
	printf("Take 2\n");

	bit *datoIn = (bit *) malloc(sizeof(bit)*10);
	memset(datoIn,0,10);
	datoIn[0] = 1;
	datoIn[1] = 0;
	datoIn[2] = 1;

	bit *enW = (bit *) malloc(sizeof(bit));
	bit *enR = (bit *) malloc(sizeof(bit));

	// Registers address
	bit *rA = (bit *) malloc(sizeof(bit)*4);
	bit *rB = (bit *) malloc(sizeof(bit)*4);
	bit *rC = (bit *) malloc(sizeof(bit)*4);
	memset(rA,0,4);
	memset(rB,0,4);
	memset(rC,0,4);
	rC[0] = 1;
	rA[0] = 1;

	// Out
	bit *oA;
	bit *oB;

	// Initialize objects
	clk = Clock();
	clk.Initialize();
	bit *signalClk = clk.Signal();

	reg = Register();
	reg.Width(10);
	reg.Initialize();
	bit *datoOut = reg.Data();
	reg.Input(datoIn);
	reg.Clk(signalClk);

	RegisterBank.Width(10);
	RegisterBank.Length(16);
	RegisterBank.Initialize();
	RegisterBank.SetControlSignals(enR, enW);
	RegisterBank.Clk(signalClk);
	oA = RegisterBank.OutA();
	oB = RegisterBank.OutB();
	RegisterBank.RegA(rA);
	RegisterBank.RegB(rB);
	RegisterBank.RegC(rC);
	RegisterBank.DataIn(datoIn);	
	*enR = 1;
	*enW = 0;

	printf("> Objects created succesfully\n");

	//while (true);

	pthread_t a;
	pthread_t b;
	pthread_t c;
	pthread_create(&a, NULL, startClock, NULL);
	pthread_create(&b, NULL, startRegister, NULL);
	pthread_create(&c, NULL, startRegisterBank, NULL);

	int i = 0;
	while(true){
		if(*signalClk == 1){
			printf("jj\n");
			//PrintData(datoOut, 10);
			printf(">> Reg A out = ");
			PrintData(oA, 10);
			i++;
			//printf(">> i = %d\n", i);
		}
		if(i==3){
			//reg.Disable();
			*enW = 1;
			datoIn[3] = 1;

		}
		if(i>=15){
			clk.Stop();
			break;
		}
		sleep(1);
	}
	pthread_join(a, NULL);
	return 0;
} 