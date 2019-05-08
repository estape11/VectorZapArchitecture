//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 08/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <Clock.hpp>
#include <InstructionMemory.hpp>
#include <Register.hpp>
#include <Pc.hpp>
#include <ScalarAlu.hpp>
#include <ControlUnit.hpp>
#include <ScalarRegisterFile.hpp>

#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable cond;
std::mutex mutex;

Clock gClk;
Pc gPc;
InstructionMemory gInstMem;
ControlUnit gControlUnit;
Register gFetchDecode;
Register gDecodeExecute;
ScalarRegisterFile gScalarRegFile;
ScalarAlu gScalarAlu;
Register gExecuteMemory;
Register gMemoryWriteBack;

void StartClk(void){
	while (true) {
		gClk.RunMutex();
		cond.notify_all();

	}
	
}

void StartClkKey(void){
	bool clk = false;
	while (fgetc(stdin)) {
		if (clk){
			printf("\u21D3");

		} else {
			printf("\u21D1");
		}
		cond.notify_all();
		clk = (clk)? false : true;
	}
	
}

void StartPc(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gPc.RunMutex();

	}
	
}

void StartInstMem(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gInstMem.RunMutex();

	}
	
}

void StartFetchDeco(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gFetchDecode.RunMutex();

	}
	
}

void StartControlUnit(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gControlUnit.RunMutex();

	}
	
}

void StartScalarRegFile(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gScalarRegFile.RunMutex();

	}

}

void StartDecoExe(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gDecodeExecute.RunMutex();

	}

}

void StartScalarAlu(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gScalarAlu.RunMutex();

	}

}

void StartExeMem(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gExecuteMemory.RunMutex();

	}

}

void StartMemWb(void){
	std::unique_lock<std::mutex> lck(mutex);
	while (true) {
		cond.wait(lck); 
		gMemoryWriteBack.RunMutex();

	}

}

int main(){
	pthread_t threads[10];
	// Clock
	gClk = Clock();
	gClk.Frequency(10); //max 350 w/o prints
	gClk.Initialize();

	// Control Unit
	gControlUnit = ControlUnit();
	gControlUnit.Initialize();

	// ------------------------------- Fetch ------------------------------- //
	// PC
	gPc = Pc();
	gPc.Width(32);
	gPc.Initialize();
	gPc.Clk(gClk.Signal());	
	gPc.SetControlSignal(gControlUnit.FetchControl());

	// Instruction Memory
	gInstMem = InstructionMemory();
	gInstMem.Width(32);
	gInstMem.Length(100);
	gInstMem.Initialize();
	gInstMem.LoadMemory("/home/estape/Desktop/Mem.ROM");
	gInstMem.Input(gPc.Data());

	// Register Fetch-Decode
	gFetchDecode = Register();
	gFetchDecode.Width(32);
	gFetchDecode.Ports(1);
	gFetchDecode.Initialize();
	gFetchDecode.Clk(gClk.Signal());
	gFetchDecode.SetControlSignal(gControlUnit.FetchDecodeEn());
	gFetchDecode.Input(gInstMem.Output(), 0); // first port

	// ------------------------------- Decode ------------------------------- //
	// Control Unit I/O
	gControlUnit.Input(gFetchDecode.Output(0)); // first port

	// Scalar Register File
	gScalarRegFile = ScalarRegisterFile();
	gScalarRegFile.Width(32);
	gScalarRegFile.AddressWidth(4);
	gScalarRegFile.Length(16);
	gScalarRegFile.Initialize();
	gScalarRegFile.Clk(gClk.Signal());
	gScalarRegFile.RegA(gFetchDecode.Output(0)+13);
	gScalarRegFile.RegB(gFetchDecode.Output(0)+17);

	// Register Decode-Execute
	gDecodeExecute = Register();
	gDecodeExecute.Width(32);
	gDecodeExecute.Ports(5);
	gDecodeExecute.Initialize();
	gDecodeExecute.Clk(gClk.Signal());
	gDecodeExecute.SetControlSignal(gControlUnit.DecodeExecuteEn());
	gDecodeExecute.Input(gControlUnit.Output(), 0); // first port
	gDecodeExecute.Input(gScalarRegFile.OutA(), 1);
	gDecodeExecute.Input(gScalarRegFile.OutB(), 2);
	gDecodeExecute.Input(gFetchDecode.Output(0)+9, 3); // Dest. Register
	gDecodeExecute.Input(gFetchDecode.Output(0)+17	, 4); // Immediate

	// ------------------------------- Execute ------------------------------- //
	// Scalar ALU
	gScalarAlu = ScalarAlu();
	gScalarAlu.Selector(gDecodeExecute.Output(0)); // control signals
	gScalarAlu.SelectorWidth(4);
	gScalarAlu.OperA(gDecodeExecute.Output(1));
	gScalarAlu.OperB(gDecodeExecute.Output(2));
	gScalarAlu.Width(32);
	gScalarAlu.Initialize();
	gScalarAlu.ImmB(gDecodeExecute.Output(4));
	gScalarAlu.SelectorOpB(gDecodeExecute.Output(0)+5);

	// Register Execute-Memory
	gExecuteMemory = Register();
	gExecuteMemory.Width(32);
	gExecuteMemory.Ports(3);
	gExecuteMemory.Initialize();
	gExecuteMemory.Clk(gClk.Signal());
	gExecuteMemory.SetControlSignal(gControlUnit.ExecuteMemoryEn());
	gExecuteMemory.Input(gDecodeExecute.Output(0), 0);
	gExecuteMemory.Input(gDecodeExecute.Output(3), 1);
	gExecuteMemory.Input(gScalarAlu.Result(), 2);

	// ------------------------------- Memory ------------------------------- //
	// Register Memory-WriteBack
	gMemoryWriteBack = Register();
	gMemoryWriteBack.Width(32);
	gMemoryWriteBack.Ports(3);
	gMemoryWriteBack.Initialize();
	gMemoryWriteBack.Clk(gClk.Signal());
	gMemoryWriteBack.SetControlSignal(gControlUnit.MemoryWriteBackEn());
	gMemoryWriteBack.Input(gExecuteMemory.Output(0), 0);
	gMemoryWriteBack.Input(gExecuteMemory.Output(1), 1);
	gMemoryWriteBack.Input(gExecuteMemory.Output(2), 2);

	// ------------------------------- WriteBack ------------------------------- //
	gScalarRegFile.SetControlSignals(gControlUnit.DecodeControl(), gMemoryWriteBack.Output(0)+4);
	gScalarRegFile.RegC(gMemoryWriteBack.Output(1));
	gScalarRegFile.DataIn(gMemoryWriteBack.Output(2));

	// Threads Creation
	std::thread t2(StartPc);
	std::thread t3(StartInstMem);
	std::thread t4(StartFetchDeco);
	std::thread t5(StartControlUnit);
	std::thread t6(StartScalarRegFile);
	std::thread t7(StartDecoExe);
	std::thread t8(StartScalarAlu);
	std::thread t9(StartExeMem);
	std::thread t10(StartMemWb);
	std::thread t1(StartClk);//std::thread t1(StartClkKey);
	
	//std::unique_lock<std::mutex> lck1(mutex);
	while (false) {
		//printf(">> Instruction on Decode >> ");
		printf(">> ");
		BaseHelper::PrintBin(gFetchDecode.Output(0),32);

		//printf(">> Control Flags (Decode) >> ");
		printf(">> ");
		BaseHelper::PrintBin(gControlUnit.Output(),10);

		//printf(">> Control Flags (Execute) >> ");
		printf(">> ");
		BaseHelper::PrintBin(gDecodeExecute.Output(0),10);

		//printf(">> Control Flags (Memory) >> ");
		printf(">> ");
		BaseHelper::PrintBin(gExecuteMemory.Output(0),10);

		//printf(">> Control Flags (WriteBack) >> ");
		printf(">> ");
		BaseHelper::PrintBin(gMemoryWriteBack.Output(0),10);

		//printf(">> Rc (WriteBack) >> ");
		printf(">> ");
		BaseHelper::PrintBin(gMemoryWriteBack.Output(1),4);

	}

	t1.join();
	//gScalarRegFile.SaveMemory("/home/estape/Desktop/t.txt");
	//pthread_join(threads[0], NULL);

	return 0;
}