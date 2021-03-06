//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 05/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <stdlib.h>
#include <string.h>
#include <Types.hpp>
#include <BaseHelper.hpp>

class VectorRegisterFile {
public:
	VectorRegisterFile(void){
		apData = NULL;
		apDataIn = NULL;
		apOutA = NULL;
		apOutB = NULL;
		apRegA = NULL;
		apRegB = NULL;
		apRegC = NULL;
		aWidth = 0;
		aLength = 0;
		aAddressWidth = 0;
		apEnableR = NULL;
		apEnableW = NULL;
		apClk = NULL;
		aRun = false;
		aWriteStatus = false;
		aReadStatus = false;
		aClock = false;
		apDump = NULL;

	}

	// Sets the input data pointer
	// @author estape11
	// @params inData
	// @return void
	void DataIn(bit *);

	// Gets the output A pointer
	// @author estape11
	// @params void
	// @return outA
	bit *OutA(void);

	// Gets the output B pointer
	// @author estape11
	// @params void
	// @return outB
	bit *OutB(void);

	// Sets the register A input pointer
	// @author estape11
	// @params regA
	// @return void
	void RegA(bit *);

	// Sets the register B input pointer
	// @author estape11
	// @params regB
	// @return void
	void RegB(bit *);

	// Sets the register C input pointer
	// @author estape11
	// @params regC
	// @return void
	void RegC(bit *);

	// Sets the control signals of RW
	// @author estape11
	// @params enableR, enableW, dump
	// @return void
	void SetControlSignals(bit *, bit *, bit *);

	// Sets the clock signal
	// @author estape11
	// @params enableR, enableW
	// @return void
	void Clk(bit *);

	// Sets the width of each cell
	// @author estape11
	// @params width
	// @return void
	void Width(int);

	// Sets the length of the register
	// @author estape11
	// @params length
	// @return void
	void Length(int);

	// Sets the width of the address
	// @author estape11
	// @params width
	// @return void
	void AddressWidth(int);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

	// Saves the memory to a file
	// @author estape11
	// @params file
	// @return void
	void SaveMemory(char *);

	// Put to run the register
	// @author estape11
	// @params void
	// @return void
	void Run(void);

	void RunMutex(void);
	
private:
	// Stored data
	bit **apData;

	// In/Out registers
	bit *apDataIn;
	bit *apOutA;
	bit *apOutB;

	// Addresses
	bit *apRegA;
	bit *apRegB;
	bit *apRegC;

	// Dimensions
	int aWidth;
	int aLength;
	int aAddressWidth;

	// Control
	bit *apEnableR;
	bit *apEnableW;
	bit *apClk;
	bool aRun;
	bool aWriteStatus;
	bool aReadStatus;
	bool aClock;
	bit *apDump;

};