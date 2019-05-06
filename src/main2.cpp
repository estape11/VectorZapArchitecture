#include <Clock.hpp>
#include <Register.hpp>
#include <ScalarRegisterFile.hpp>
#include <Types.hpp>
#include <ScalarAlu.hpp>
#include <InstructionMemory.hpp>
#include <VectorRegisterFile.hpp>

#include <pthread.h>
#include <string.h>
#include <math.h>

Clock clk;
Register reg;
ScalarRegisterFile RegisterBank;
ScalarAlu scalarAlu;
InstructionMemory rom;
VectorRegisterFile vectorBank;

void* startRegisterBank(void* args){
	RegisterBank.Run();
	pthread_exit(NULL);

}

void* startVectorBank(void* args){
	vectorBank.Run();
	pthread_exit(NULL);

}


void* startRom(void* args){
	rom.Run();
	pthread_exit(NULL);

}

void* startALU(void* args){
	scalarAlu.Run();
	pthread_exit(NULL);

}

void* startRegister(void* args){
	//reg.Enable();
	//bit *enable = (bit *) malloc(sizeof(bit));
	char enable = 1;
	reg.SetControlSignal(&enable);
	reg.Run();
	pthread_exit(NULL);

}
void* startClkKey(void* args){
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
	bit *vEnW = (bit *) malloc(sizeof(bit));
	bit *vEnR = (bit *) malloc(sizeof(bit));

	// Registers address
	bit *rA = (bit *) malloc(sizeof(bit)*4);
	bit *rB = (bit *) malloc(sizeof(bit)*4);
	bit *rC = (bit *) malloc(sizeof(bit)*4);
	memset(rA,0,4);
	memset(rB,0,4);
	memset(rC,0,4);
	rC[0] = 1; // Reg 1
	rA[0] = 1;

	// Out
	bit *oA;
	bit *oB;
	bit *vOA;
	bit *vOB;

	// Initialize objects
	clk = Clock();
	clk.Initialize();
	bit *signalClk = clk.Signal();

	bit selector[] = {1,1,0,0};
	bit operA[] = {1,1,1,0};
	bit operB[] = {1,0,1,0};
	printf("> operA = ");
	BaseHelper::PrintBin(operA, 4);
	printf("> operB = ");
	BaseHelper::PrintBin(operB, 4);
	scalarAlu = ScalarAlu();
	scalarAlu.Selector(selector);
	scalarAlu.SelectorWidth(4);
	scalarAlu.OperA(operA);
	scalarAlu.OperB(operB);
	scalarAlu.Width(4);
	scalarAlu.Initialize();
	bit *resu = scalarAlu.Result();

	rom = InstructionMemory();
	rom.Width(32);
	rom.Length(100);
	rom.Initialize();
	bit *inRom = (bit *) malloc(sizeof(bit)*32);
	memset(inRom,0,32);
	//inRom[0] = 1;
	//inRom[1] = 1;
	//inRom[2] = 1;
	rom.Input(inRom);
	bit *outRom = rom.Output();
	rom.LoadMemory("/home/estape/Desktop/Mem.ROM");

	reg = Register();
	reg.Width(10);
	reg.Initialize();
	bit *datoOut = reg.Data();
	reg.Input(datoIn);
	reg.Clk(signalClk);

	RegisterBank.Width(10);
	RegisterBank.AddressWidth(4);
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

	vectorBank = VectorRegisterFile();
	vectorBank.Width(16);
	vectorBank.AddressWidth(4);
	vectorBank.Length(16);
	vectorBank.Initialize();
	vectorBank.SetControlSignals(vEnR, vEnW);
	vectorBank.Clk(signalClk);
	vOA = vectorBank.OutA();
	vOB = vectorBank.OutB();
	bit *vectorA = BaseHelper::DecimalToBin(2,4);
	bit *vectorB = BaseHelper::DecimalToBin(0,4);
	bit *vectorC = BaseHelper::DecimalToBin(2,4);
	vectorBank.RegA(vectorA);
	vectorBank.RegB(vectorB);
	vectorBank.RegC(vectorC);
	bit *dataVector = (bit *) malloc(sizeof(bit)*8);
	vectorBank.DataIn(dataVector);
	*vEnR = 0;
	*vEnW = 0;


	printf("> Objects created succesfully\n");

	//while (true);

	pthread_t a;
	pthread_t b;
	pthread_t c;
	pthread_t d;
	pthread_t e;
	pthread_t f;
	pthread_create(&b, NULL, startRegister, NULL);
	pthread_create(&c, NULL, startRegisterBank, NULL);
	pthread_create(&d, NULL, startALU, NULL);
	pthread_create(&a, NULL, startClock, NULL);
	pthread_create(&e, NULL, startRom, NULL);
	pthread_create(&f, NULL, startVectorBank, NULL);

	int i = 0;
	int j = 0;
	while(true){
		if(*signalClk == 1){
			printf(">> Reg A out = ");
			BaseHelper::PrintBin(oA, 10);
			printf(">> Reg Vect A out = ");
			BaseHelper::PrintBin(vOA, 8);
			printf(">> ALU = ");
			BaseHelper::PrintBin(resu, 4);
			printf(">> ROM = ");
			BaseHelper::PrintBin(outRom, 32);
			i++;
			memcpy(inRom, BaseHelper::DecimalToBin(i,32), 32);
			//printf(">> i = %d\n", i);
		} else{
			j++;
		}
		if(i==0){
			*vEnW = 1;
			printf(">>> Writing 7 \n");
			memcpy(dataVector, BaseHelper::DecimalToBin(7,8), 8);
		}
		if(i==1){
			printf(">>> Writing 10 \n");
			memcpy(dataVector, BaseHelper::DecimalToBin(10,8), 8);
		}
		if(i==2){
			*vEnW = 0;
		}
		if(i==3){
			//reg.Disable();
			*vEnR = 1;
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