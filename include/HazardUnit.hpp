//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 11/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <Types.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <BaseHelper.hpp>

class HazardUnit {
public:
	HazardUnit(void){
		apScalarA = NULL;
		apScalarB = NULL;

		apImmSel = NULL;

		apRa = NULL;
		apRb = NULL;

		apMode = NULL;

		apVectorA = NULL;
		apVectorB = NULL;

		apDataMem = NULL;
		apScalarDataExe = NULL;
		apDataWb = NULL;
		apScalarDataExe = NULL;

		apRcMem = NULL;
		apRcExe = NULL;
		apRcWb = NULL;

		apModeMem = NULL;
		apModeExe = NULL;
		apModeWb = NULL;

		apVectorOutA = NULL;
		apVectorOutB = NULL;
		apScalarOutA = NULL;
		apScalarOutB = NULL;

		aWidth = 0;
		aRun = false;

	}

	// Sets
	// @author estape11
	// @params
	// @return void
	void ScalarInput(bit *, bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void ImmSel(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void RegAddress(bit *, bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void Mode(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void VectorInput(bit *, bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void DataMem(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void ScalarDataExe(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void DataWb(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void VectorDataExe(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void RcMem(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void RcExe(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void RcWb(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void ModeMem(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void ModeExe(bit *);

	// Sets
	// @author estape11
	// @params
	// @return void
	void ModeWb(bit *);

	// Gets
	// @author estape11
	// @params void
	// @return 
	bit *VectorOutA(void);

	// Gets
	// @author estape11
	// @params void
	// @return 
	bit *VectorOutB(void);

	// Gets
	// @author estape11
	// @params void
	// @return 
	bit *ScalarOutA(void);

	// Gets
	// @author estape11
	// @params void
	// @return 
	bit *ScalarOutB(void);

	// Sets
	// @author estape11
	// @params
	// @return void
	void Width(int);

	// Initialize the memory
	// @author estape11
	// @params void
	// @return void
	void Initialize(void);

	// Start the Hazard unit
	// @author estape11
	// @params
	// @return void
	void Run(void);

private:
	bit *apScalarA;
	bit *apScalarB;

	bit *apImmSel;

	bit *apRa;
	bit *apRb;

	bit *apMode;

	bit *apVectorA;
	bit *apVectorB;

	bit *apDataMem;
	bit *apScalarDataExe;
	bit *apDataWb;
	bit *apVectorDataExe;

	bit *apRcMem;
	bit *apRcExe;
	bit *apRcWb;

	bit *apModeMem;
	bit *apModeExe;
	bit *apModeWb;

	bit *apVectorOutA;
	bit *apVectorOutB;
	bit *apScalarOutA;
	bit *apScalarOutB;

	int aWidth;
	bool aRun;
};