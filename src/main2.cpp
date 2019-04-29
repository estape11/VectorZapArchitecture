#include <Clock.hpp>
#include <Register.hpp>
#include <BaseHelper.hpp>

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
	clk.Frequency(100);
	//clk.Signal((char*)args);
	clk.Run();
	pthread_exit(NULL);
}

int main(int argc, const char* argv[]){
	printf("Take 2\n");

	char* datoIn = (char *) malloc(sizeof(char)*10);
	char* datoIn2 = (char *) malloc(sizeof(char)*10);

	char ** twoD = (char**) malloc(sizeof(char*)*10);

	for(int i=0;i<10;i++){
		twoD[i] = (char *) malloc(sizeof(char)*32);
		memset(twoD[i],0,32);
		printf(">> ");
		PrintData(twoD[i] , 32);
	}	

	strncpy(datoIn2, datoIn, 10);
	memset(datoIn,0,10);
	datoIn[0] = 0x1;
	datoIn[1] = 0x0;
	datoIn[2] = 0x1;
	BaseHelper baseHelper = BaseHelper();
	datoIn = baseHelper.DecimalToBin(19, 3);

	printf(">> ");
	PrintData(datoIn, 10);
	printf(">> %d\n", baseHelper.BinToDecimal(datoIn, 10) );

	// Initialize objects
	reg = Register();
	reg.Width(10);
	reg.Initialize();
	char* datoOut = reg.Data();
	reg.Input(datoIn);

	clk = Clock();
	clk.Initialize();

	char* signalClk = clk.Signal();

	reg.Clk(signalClk);
	//while (true);

	pthread_t a;
	pthread_t b;
	pthread_create(&a, NULL, startALU, NULL);
	pthread_create(&b, NULL, startRegister, NULL);

	int i = 0;
	while(true){
		if(*signalClk == 1){
			PrintData(datoOut, 10);
			i++;
			printf(">> i = %d\n", i);
		}
		if(i==40000){
			//reg.Disable();
			datoIn[3] = 1;
		}
		if(i>=1000000){
			clk.Stop();
			break;
		}
	}
	pthread_join(a, NULL);
	return 0;
} 