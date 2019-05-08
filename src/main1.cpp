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

// Initial Implementation

#include <Clock.hpp>
#include <InstructionMemory.hpp>
#include <Register.hpp>
#include <Pc.hpp>
#include <ScalarAlu.hpp>
#include <ControlUnit.hpp>
#include <ScalarRegisterFile.hpp>

#include <pthread.h>

// Global Objects
static Clock gClk;
InstructionMemory gInstMem;
Pc gPc;
ControlUnit gControlUnit;
ScalarRegisterFile gScalarRegFile;
ScalarAlu gScalarAlu;
Register gFetchDecode;
Register gDecodeExecuteData1;
Register gDecodeExecuteData2;
Register gDecodeExecuteData3;
Register gDecodeExecuteControl;
Register gExecuteMemoryData1;
Register gExecuteMemoryData2;
Register gExecuteMemoryControl;
Register gMemoryWriteBackData1;
Register gMemoryWriteBackData2;
Register gMemoryWriteBackControl;

// Control Signals
bit *gpClkSignal;

void *StartClk(void *args){
	gClk.Run();
	pthread_exit(NULL);

}

void *StartClkKeys(void *args){
	gClk.RunKeyboard();
	pthread_exit(NULL);

}

void *StartPc(void *args){
	gPc.Run();
	pthread_exit(NULL);
	
}

void *StartInstMem(void *args){
	gInstMem.Run();
	pthread_exit(NULL);
	
}

void *StartFetchDeco(void *args){
	gFetchDecode.Run();
	pthread_exit(NULL);
	
}

void *StartControlUnit(void *args){
	gControlUnit.Run();
	pthread_exit(NULL);
	
}

void *StartDecoExeData1(void *args){
	gDecodeExecuteData1.Run();
	pthread_exit(NULL);

}

void *StartDecoExeData2(void *args){
	gDecodeExecuteData2.Run();
	pthread_exit(NULL);

}

void *StartDecoExeData3(void *args){
	gDecodeExecuteData3.Run();
	pthread_exit(NULL);

}

void *StartDecoExeControl(void *args){
	gDecodeExecuteControl.Run();
	pthread_exit(NULL);

}

void *StartScalarRegFile(void *args){
	gScalarRegFile.Run();
	pthread_exit(NULL);

}

void *StartScalarAlu(void *args){
	gScalarAlu.Run();
	pthread_exit(NULL);

}

void *StartExeMemData1(void *args){
	gExecuteMemoryData1.Run();
	pthread_exit(NULL);

}

void *StartExeMemData2(void *args){
	gExecuteMemoryData2.Run();
	pthread_exit(NULL);

}

void *StartExeMemControl(void *args){
	gExecuteMemoryControl.Run();
	pthread_exit(NULL);

}

void *StartMemWbData1(void *args){
	gMemoryWriteBackData1.Run();
	pthread_exit(NULL);

}

void *StartMemWbData2(void *args){
	gMemoryWriteBackData2.Run();
	pthread_exit(NULL);

}

void *StartMemWbControl(void *args){
	gMemoryWriteBackControl.Run();
	pthread_exit(NULL);

}

int main(int argc, const char *argv[]){
	// Threads ID's
	pthread_t threads[21];

	// Control Unit
	gControlUnit = ControlUnit();
	gControlUnit.Initialize();

	// Clock
	gClk = Clock();
	gClk.Initialize();
	gClk.Frequency(1);
	gpClkSignal = gClk.Signal();

	// ------------------------------- Fetch ------------------------------- //
	// Program Counter
	gPc = Pc();
	gPc.Width(32);
	gPc.Initialize();
	gPc.Clk(gpClkSignal);	

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
	gFetchDecode.Initialize();
	gFetchDecode.Clk(gpClkSignal);
	gFetchDecode.SetControlSignal(gControlUnit.FetchDecodeEn());
	gFetchDecode.Input(gInstMem.Output());

	// ------------------------------- Decode ------------------------------- //
	// Control Unit I/O
	gControlUnit.Input(gFetchDecode.Data());
	gPc.SetControlSignal(gControlUnit.FetchControl());

	// Scalar Register File
	gScalarRegFile = ScalarRegisterFile();
	gScalarRegFile.Width(32);
	gScalarRegFile.AddressWidth(4);
	gScalarRegFile.Length(16);
	gScalarRegFile.Initialize();
	// TEMP
	//bit *en = (bit *) malloc(sizeof(bit));
	//*en = 0; // To not write
	
	gScalarRegFile.Clk(gpClkSignal);
	gScalarRegFile.RegA(gFetchDecode.Data()+13);
	gScalarRegFile.RegB(gFetchDecode.Data()+17);
	// gScalarRegFile.RegC(rC); not yet
	// gScalarRegFile.DataIn(datoIn); not yet

	// Register Decode-Execute
	gDecodeExecuteData1 = Register();
	gDecodeExecuteData1.Width(32);
	gDecodeExecuteData1.Initialize();
	gDecodeExecuteData1.Clk(gpClkSignal);
	gDecodeExecuteData1.SetControlSignal(gControlUnit.DecodeExecuteEn());
	gDecodeExecuteData1.Input(gScalarRegFile.OutA());

	gDecodeExecuteData2 = Register();
	gDecodeExecuteData2.Width(32);
	gDecodeExecuteData2.Initialize();
	gDecodeExecuteData2.Clk(gpClkSignal);
	gDecodeExecuteData2.SetControlSignal(gControlUnit.DecodeExecuteEn());
	gDecodeExecuteData2.Input(gScalarRegFile.OutB());

	gDecodeExecuteData3 = Register();
	gDecodeExecuteData3.Width(4);
	gDecodeExecuteData3.Initialize();
	gDecodeExecuteData3.Clk(gpClkSignal);	
	gDecodeExecuteData3.SetControlSignal(gControlUnit.DecodeExecuteEn());
	gDecodeExecuteData3.Input(gFetchDecode.Data()+9);

	gDecodeExecuteControl = Register();
	gDecodeExecuteControl.Width(10); // Related with the number of control-signals
	gDecodeExecuteControl.Initialize();
	gDecodeExecuteControl.Clk(gpClkSignal);	
	gDecodeExecuteControl.SetControlSignal(gControlUnit.DecodeExecuteEn());
	gDecodeExecuteControl.Input(gControlUnit.Output());

	// ------------------------------- Execute ------------------------------- //
	// Scalar ALU
	gScalarAlu = ScalarAlu();
	gScalarAlu.Selector(gDecodeExecuteControl.Data());
	gScalarAlu.SelectorWidth(4);
	gScalarAlu.OperA(gDecodeExecuteData1.Data());
	gScalarAlu.OperB(gDecodeExecuteData2.Data());
	gScalarAlu.Width(32);
	gScalarAlu.Initialize();

	// Register Execute-Memory
	gExecuteMemoryData1 = Register();
	gExecuteMemoryData1.Width(32);
	gExecuteMemoryData1.Initialize();
	gExecuteMemoryData1.Clk(gpClkSignal);
	gExecuteMemoryData1.SetControlSignal(gControlUnit.ExecuteMemoryEn());
	gExecuteMemoryData1.Input(gScalarAlu.Result());

	gExecuteMemoryData2 = Register();
	gExecuteMemoryData2.Width(4);
	gExecuteMemoryData2.Initialize();
	gExecuteMemoryData2.Clk(gpClkSignal);	
	gExecuteMemoryData2.SetControlSignal(gControlUnit.ExecuteMemoryEn());
	gExecuteMemoryData2.Input(gDecodeExecuteData3.Data());

	gExecuteMemoryControl = Register();
	gExecuteMemoryControl.Width(10); // Related with the number of control-signals
	gExecuteMemoryControl.Initialize();
	gExecuteMemoryControl.Clk(gpClkSignal);	
	gExecuteMemoryControl.SetControlSignal(gControlUnit.ExecuteMemoryEn());
	gExecuteMemoryControl.Input(gDecodeExecuteControl.Data());

	// ------------------------------- Memory ------------------------------- //
	// Register Memory-WriteBack
	gMemoryWriteBackData1 = Register();
	gMemoryWriteBackData1.Width(32);
	gMemoryWriteBackData1.Initialize();
	gMemoryWriteBackData1.Clk(gpClkSignal);
	gMemoryWriteBackData1.SetControlSignal(gControlUnit.MemoryWriteBackEn());
	gMemoryWriteBackData1.Input(gExecuteMemoryData1.Data());

	gMemoryWriteBackData2 = Register();
	gMemoryWriteBackData2.Width(4);
	gMemoryWriteBackData2.Initialize();
	gMemoryWriteBackData2.Clk(gpClkSignal);	
	gMemoryWriteBackData2.SetControlSignal(gControlUnit.MemoryWriteBackEn());
	gMemoryWriteBackData2.Input(gExecuteMemoryData2.Data());

	gMemoryWriteBackControl = Register();
	gMemoryWriteBackControl.Width(10); // Related with the number of control-signals
	gMemoryWriteBackControl.Initialize();
	gMemoryWriteBackControl.Clk(gpClkSignal);	
	gMemoryWriteBackControl.SetControlSignal(gControlUnit.MemoryWriteBackEn());
	gMemoryWriteBackControl.Input(gExecuteMemoryControl.Data());

	// ------------------------------- WriteBack ------------------------------- //
	// Scalar Register File
	gScalarRegFile.SetControlSignals(gControlUnit.DecodeControl(), gMemoryWriteBackControl.Data()+4); // correct EnableW missing
	gScalarRegFile.RegC(gMemoryWriteBackData2.Data());
	gScalarRegFile.DataIn(gMemoryWriteBackData1.Data());

	// Thread Creation
	pthread_create(&threads[0], NULL, StartPc, NULL);
	pthread_create(&threads[1], NULL, StartInstMem, NULL);
	pthread_create(&threads[2], NULL, StartFetchDeco, NULL);
	pthread_create(&threads[3], NULL, StartControlUnit, NULL);
	pthread_create(&threads[4], NULL, StartDecoExeData1, NULL);
	pthread_create(&threads[5], NULL, StartDecoExeData2, NULL);
	pthread_create(&threads[6], NULL, StartDecoExeData3, NULL);
	pthread_create(&threads[7], NULL, StartDecoExeControl, NULL);
	pthread_create(&threads[8], NULL, StartScalarRegFile, NULL);
	pthread_create(&threads[9], NULL, StartScalarAlu, NULL);
	pthread_create(&threads[10], NULL, StartExeMemData1, NULL);
	pthread_create(&threads[11], NULL, StartExeMemData2, NULL);
	pthread_create(&threads[12], NULL, StartExeMemControl, NULL);
	pthread_create(&threads[13], NULL, StartMemWbData1, NULL);
	pthread_create(&threads[14], NULL, StartMemWbData2, NULL);
	pthread_create(&threads[15], NULL, StartMemWbControl, NULL);

	pthread_create(&threads[20], NULL, StartClk, NULL);

	while (true) {
		//BaseHelper::PrintBin(gFetchDecode.Data()+9, 4);
		//BaseHelper::PrintBin(gControlUnit.Output(), 10);
		//BaseHelper::PrintBin(gMemoryWriteBackData2.Data(), 4);
		if (*gpClkSignal == 1){
			BaseHelper::PrintBin(gExecuteMemoryData2.Data(), 4);
			BaseHelper::PrintBin(gMemoryWriteBackControl.Data()+4, 1);
		}
	}

	pthread_join(threads[20], NULL);
	printf("> Cycles = %d\n", gClk.Cycles());
	return 0;

}