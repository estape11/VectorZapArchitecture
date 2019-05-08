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

#include <Types.hpp>
#include <BaseHelper.hpp>

class ControlUnit {
public:
	ControlUnit(void) {
		apInput = NULL;
		apOutput = NULL;
		apFetchControl = NULL;
		apDecodeControl = NULL;
		apFetchDecodeEn = NULL;
		apDecodeExecuteEn = NULL;
		apExecuteMemoryEn = NULL;
		apMemoryWriteBackEn = NULL;
		aRun = false;
		
	}

	// Sets the input
	// @author estape11
	// @params instruction
	// @return void
	void Input(bit *);

	// Gets the output
	// @author estape11
	// @params void
	// @return output
	bit *Output(void);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

	// Gets the fetch control
	// @author estape11
	// @params void
	// @return fetch
	bit *FetchControl(void);

	// Gets the decode control
	// @author estape11
	// @params void
	// @return decode
	bit *DecodeControl(void);

	// Gets the fetchdecode enable
	// @author estape11
	// @params void
	// @return fetchdecode
	bit *FetchDecodeEn(void);

	// Gets the decodeexecute enable
	// @author estape11
	// @params void
	// @return decodeexecute
	bit *DecodeExecuteEn(void);

	// Gets the executememory enable
	// @author estape11
	// @params void
	// @return executememory
	bit *ExecuteMemoryEn(void);

	// Gets the memorywriteback enable
	// @author estape11
	// @params void
	// @return memorywriteback
	bit *MemoryWriteBackEn(void);

	// Starts the Control Unit
	// @author estape11
	// @params void
	// @return void
	void Run(void);

	void RunMutex(void);
	
private:
	// I/O registers
	bit *apInput;
	bit *apOutput;

	// Direct Control
	bit *apFetchControl;
	bit *apDecodeControl;

	// Pipeline registers
	bit *apFetchDecodeEn;
	bit *apDecodeExecuteEn;
	bit *apExecuteMemoryEn;
	bit *apMemoryWriteBackEn;

	bool aRun;

};