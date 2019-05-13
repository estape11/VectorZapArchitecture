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

#include <ControlUnit.hpp>

void ControlUnit::Input(bit *pInput){
	apInput = pInput;

}

bit *ControlUnit::Output(void){
	return apOutput;

}

bit *ControlUnit::FetchControl(void){
	return apFetchControl;

}

bit *ControlUnit::DecodeControl(void){
	return apDecodeControl;

}

bit *ControlUnit::FetchDecodeEn(void){
	return apFetchDecodeEn;

}

bit *ControlUnit::DecodeExecuteEn(void){
	return apDecodeExecuteEn;

}

bit *ControlUnit::ExecuteMemoryEn(void){
	return apExecuteMemoryEn;

}

bit *ControlUnit::MemoryWriteBackEn(void){
	return apMemoryWriteBackEn;

}

void ControlUnit::Initialize(void){
	// Modify every time is a signal added
	apOutput = (bit *) malloc(sizeof(bit)*32);
	memset(apOutput, 0, 32);
	apDecodeControl = (bit *) malloc(sizeof(bit)*2); // For vector/scalar
	memset(apDecodeControl, 0, 2);
	apFetchControl = (bit *) malloc(sizeof(bit)*1);
	*apFetchControl = 1;
	apFetchDecodeEn = (bit *) malloc(sizeof(bit));
	apDecodeExecuteEn = (bit *) malloc(sizeof(bit));
	apExecuteMemoryEn = (bit *) malloc(sizeof(bit));
	apMemoryWriteBackEn = (bit *) malloc(sizeof(bit));

	// Sets the pipe-registers enable
	*apFetchDecodeEn = 1;
	*apDecodeExecuteEn = 1;
	*apExecuteMemoryEn = 1;
	*apMemoryWriteBackEn = 1;	

}

void ControlUnit::Run(void){
	aRun = true;
	while (aRun) {
		// Mode
		if (apInput[1] == 0 && apInput[0] == 0) { // NOP
			if(apInput[3] == 1 && apInput[2] == 1) { // Halt
				// Stops the pipeline				
				*apFetchControl = 0;
				*apFetchDecodeEn = 0;
				*apDecodeExecuteEn = 0;
				*apExecuteMemoryEn = 0;
				*apMemoryWriteBackEn = 0;

			} else { // NOP
				memset(apOutput, 0, 32);
				*apDecodeControl = 0;
				
			}

		} else if (apInput[1] == 0 && apInput[0] == 1) { // Scalar - Scalar
			if(apInput[3] == 0 && apInput[2] == 0) { // Type A
				memcpy(apOutput, apInput+5, 4); // Alu Sel
				apOutput[4] = 1; // Scalar Reg Write
				*apDecodeControl = 1;

			}

		} else if (apInput[1] == 1 && apInput[0] == 0) { // Vector - Vector
			memset(apOutput, 0, 32);
			*apDecodeControl = 0;

		} else if (apInput[1] == 1 && apInput[0] == 1) { // Vector - Scalar
			memset(apOutput, 0, 32);
			*apDecodeControl = 0;

		} else {
			memset(apOutput, 0, 32);
			*apDecodeControl = 0;
			printf("Error: Unknown mode\n");

		}

	}

}

void ControlUnit::RunMutex(void){
	// Mode
	if (apInput[1] == 0 && apInput[0] == 0) { // NOP
		if (apInput[3] == 1 && apInput[2] == 1) { // Halt
			memset(apOutput, 0, 32);
			memset(apDecodeControl, 0, 2);
			// Stops the pipeline				
			*apFetchControl = 0;
			*apFetchDecodeEn = 0;
			*apDecodeExecuteEn = 0;
			*apExecuteMemoryEn = 0;
			*apMemoryWriteBackEn = 0;

		} else { // NOP
			if (BaseHelper::BinToDecimal(apInput+5, 4) == 15){
				memset(apOutput, 0, 32);
				memset(apDecodeControl, 0, 2);
				printf("> Memory Dump \n");
				// Memory Dump
				apOutput[14] = 1;
				
			} else {
				memset(apOutput, 0, 32);
				memset(apDecodeControl, 0, 2);

			}
		}

	} else if (apInput[1] == 0 && apInput[0] == 1) { // Scalar - Scalar
		memset(apOutput, 0, 32);
		memset(apDecodeControl, 0, 2);
		if (apInput[3] == 0 && apInput[2] == 0) { // Type A
			// Scalar Reg Read
			apDecodeControl[0] = 1;

			// Vector Reg Read
			// Stays in zero

			// Scalar Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // Oper +
					// All in zero
					break;

				case 0x1: // Oper -
					apOutput[0] = 1;
					break;
			}

			// Scalar Reg Write
			apOutput[4] = 1;

			// Immediate
			apOutput[5] = apInput[4];

			// Vector Reg Write
			// Stays in zero

			// InSel
			// Stays in zero

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			// Stays in zero

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else if (apInput[3] == 0 && apInput[2] == 1) { // Type L
			// Scalar Reg Read
			apDecodeControl[0] = 1;

			// Vector Reg Read
			// Stays in zero

			// Scalar Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // AND
					// Alu sel
					apOutput[0] = 1;
					apOutput[1] = 1;
					break;

				case 0x1: // OR
					apOutput[1] = 1;
					break;

				case 0x2: // XOR
					apOutput[2] = 1;
					break;

				case 0x3: // Shift R
					apOutput[1] = 1;
					apOutput[2] = 1;
					break;

				case 0x4: // Shift L
					apOutput[0] = 1;
					apOutput[2] = 1;
					break;

				case 0x5: // Circular Shift R
					apOutput[2] = 1;
					apOutput[3] = 1;
					break;

				case 0x6: // Circular Shift L
					apOutput[0] = 1;
					apOutput[1] = 1;
					apOutput[3] = 1;
					break;
			}

			// Scalar Reg Write
			apOutput[4] = 1;

			// Immediate
			apOutput[5] = apInput[4];

			// Vector Reg Write
			// Stays in zero

			// InSel
			// Stays in zero

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			// Stays in zero

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else if (apInput[3] == 1 && apInput[2] == 0){ // Type D
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			if (tempOpCode == 0) { // Assignation
				// Scalar Reg Read
				apDecodeControl[0] = 1;

				// Vector Reg Read
				// Stays in zero

				// Scalar Alu Sel
				apOutput[1] = 1;
				apOutput[3] = 1;

				// Scalar Reg Write
				apOutput[4] = 1;

				// Immediate
				apOutput[5] = apInput[4];

				// Vector Reg Write
				// Stays in zero

				// InSel
				// Stays in zero

				// Mem Read
				// Stays in zero

				// Mem Write
				// Stays in zero

				// Vector Alu Sel
				// Stays in zero

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];

			} else if (tempOpCode == 1) { // Store
				// Scalar Reg Read
				apDecodeControl[0] = 1;

				// Vector Reg Read
				// Stays in zero

				// Scalar Alu Sel
				apOutput[0] = 1;
				apOutput[3] = 1;

				// Scalar Reg Write
				// Stays in zero

				// Immediate
				apOutput[5] = apInput[4];

				// Vector Reg Write
				// Stays in zero

				// InSel
				// Stays in zero

				// Mem Read
				// Stays in zero

				// Mem Write
				apOutput[9] = 1;

				// Vector Alu Sel
				// Stays in zero

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];

			} else if (tempOpCode == 2) { // Load
				// Scalar Reg Read
				apDecodeControl[0] = 1;

				// Vector Reg Read
				// Stays in zero

				// Scalar Alu Sel
				apOutput[1] = 1;
				apOutput[3] = 1;

				// Scalar Reg Write
				apOutput[4] = 1;

				// Immediate
				apOutput[5] = apInput[4];

				// Vector Reg Write
				// Stays in zero

				// InSel
				// Stays in zero

				// Mem Read
				apOutput[8] = 1;

				// Mem Write
				// Stays in zero

				// Vector Alu Sel
				// Stays in zero

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];

			}

		}

	} else if (apInput[1] == 1 && apInput[0] == 0) { // Vector - Vector
		memset(apOutput, 0, 32);
		memset(apDecodeControl, 0, 2);
		if (apInput[3] == 0 && apInput[2] == 0) { // Type A
			// Scalar Reg Read
			// Stays in zero

			// Vector Reg Read
			apDecodeControl[1] = 1; 

			// Scalar Alu Sel
			// Stays in zero

			// Scalar Reg Write
			// Stays in zero

			// Immediate
			// Stays in zero

			// Vector Reg Write
			apOutput[6] = 1;

			// InSel
			apOutput[7] = 1;

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // Oper +
					// All in zero
					break;

				case 0x1: // Oper -
					apOutput[10] = 1;
					break;
			}

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else 	if (apInput[3] == 0 && apInput[2] == 1) { // Type A
			// Scalar Reg Read
			// Stays in zero

			// Vector Reg Read
			apDecodeControl[1] = 1; 

			// Scalar Alu Sel
			// Stays in zero

			// Scalar Reg Write
			// Stays in zero

			// Immediate
			// Stays in zero

			// Vector Reg Write
			apOutput[6] = 1;

			// InSel
			apOutput[7] = 1;

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // AND
					apOutput[10] = 1;
					apOutput[11] = 1;
					break;

				case 0x1: // OR
					apOutput[11] = 1;
					break;

				case 0x2: // XOR
					apOutput[12] = 1;
					break;

				case 0x3: // Shift R
					apOutput[11] = 1;
					apOutput[12] = 1;
					break;

				case 0x4: // Shift L
					apOutput[10] = 1;
					apOutput[12] = 1;
					break;

				case 0x5: // Circular Shift R
					apOutput[12] = 1;
					apOutput[13] = 1;
					break;

				case 0x6: // Circular Shift L
					apOutput[10] = 1;
					apOutput[11] = 1;
					apOutput[13] = 1;
					break;
			}

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else if (apInput[3] == 1 && apInput[2] == 0){ // Type D
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			if (tempOpCode == 0) { // Assignation
				// Scalar Reg Read
				// Stays in zero

				// Vector Reg Read
				apDecodeControl[1] = 1;

				// Scalar Alu Sel
				// Stays in zero

				// Scalar Reg Write
				// Stays in zero

				// Immediate
				// Stays in zero

				// Vector Reg Write
				apOutput[6] = 1;

				// InSel
				apOutput[7] = 1;

				// Mem Read
				// Stays in zero

				// Mem Write
				// Stays in zero

				// Vector Alu Sel
				apOutput[11] = 1;
				apOutput[13] = 1;

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];

			}

		}

	} else if (apInput[1] == 1 && apInput[0] == 1) { // Vector - Scalar
		memset(apOutput, 0, 32);
		memset(apDecodeControl, 0, 2);
		if (apInput[3] == 0 && apInput[2] == 0) { // Type A
			// Scalar Reg Read
			apDecodeControl[0] = 1;

			// Vector Reg Read
			apDecodeControl[1] = 1;

			// Scalar Alu Sel
			// Stays in zero

			// Scalar Reg Write
			// Stays in zero

			// Immediate
			apOutput[5] = 1; // to use a scalar as operator

			// Vector Reg Write
			apOutput[6] = 1;

			// InSel
			apOutput[7] = 1;

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // Oper +
					// All in zero
					break;

				case 0x1: // Oper -
					apOutput[10] = 1;
					break;
			}

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else if (apInput[3] == 0 && apInput[2] == 1) { // Type L
			// Scalar Reg Read
			apDecodeControl[0] = 1;

			// Vector Reg Read
			apDecodeControl[1] = 1;

			// Scalar Alu Sel
			// Stays in zero

			// Scalar Reg Write
			// Stays in zero

			// Immediate
			apOutput[5] = 1; // to use a scalar as operator

			// Vector Reg Write
			apOutput[6] = 1;

			// InSel
			apOutput[7] = 1;

			// Mem Read
			// Stays in zero

			// Mem Write
			// Stays in zero

			// Vector Alu Sel
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			switch (tempOpCode) {
				case 0x0: // AND
					apOutput[10] = 1;
					apOutput[11] = 1;
					break;

				case 0x1: // OR
					apOutput[11] = 1;
					break;

				case 0x2: // XOR
					apOutput[12] = 1;
					break;

				case 0x3: // Shift R
					apOutput[11] = 1;
					apOutput[12] = 1;
					break;

				case 0x4: // Shift L
					apOutput[10] = 1;
					apOutput[12] = 1;
					break;

				case 0x5: // Circular Shift R
					apOutput[12] = 1;
					apOutput[13] = 1;
					break;

				case 0x6: // Circular Shift L
					apOutput[10] = 1;
					apOutput[11] = 1;
					apOutput[13] = 1;
					break;
			}

			// Mode
			apOutput[15] = apInput[0];
			apOutput[16] = apInput[1];

		} else if (apInput[3] == 1 && apInput[2] == 0){ // Type D
			int tempOpCode = BaseHelper::BinToDecimal(apInput+5, 4);
			if (tempOpCode == 1) { // Store
				// Scalar Reg Read
				apDecodeControl[0] = 1;

				// Vector Reg Read
				apDecodeControl[1] = 1;

				// Scalar Alu Sel
				apOutput[1] = 1;
				apOutput[3] = 1;

				// Scalar Reg Write
				// Stays in zero

				// Immediate
				apOutput[5] = apInput[4];

				// Vector Reg Write
				// Stays in zero

				// InSel
				apOutput[7] = 1;

				// Mem Read
				// Stays in zero

				// Mem Write
				apOutput[9] = 1;

				// Vector Alu Sel
				apOutput[10] = 1;
				apOutput[13] = 1;

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];
				
			} else if (tempOpCode == 2) { // Load
				// Scalar Reg Read
				apDecodeControl[0] = 1;

				// Vector Reg Read
				// Stays in zero

				// Scalar Alu Sel
				apOutput[1] = 1;
				apOutput[3] = 1;

				// Scalar Reg Write
				// Stays in zero

				// Immediate
				apOutput[5] = apInput[4];

				// Vector Reg Write
				apOutput[6] = 1;

				// InSel
				apOutput[7] = 1;

				// Mem Read
				apOutput[8] = 1;

				// Mem Write
				// Stays in zero

				// Vector Alu Sel
				// Stays in zero

				// Mode
				apOutput[15] = apInput[0];
				apOutput[16] = apInput[1];
				
			}
		}

	} else {
		memset(apOutput, 0, 32);
		memset(apDecodeControl, 0, 2);
		printf("Error: Unknown mode\n");

	}

}