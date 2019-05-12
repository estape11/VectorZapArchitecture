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

#include <HazardUnit.hpp>

void HazardUnit::ScalarInput(bit *pScalarA, bit *pScalarB){
	apScalarA = pScalarA;
	apScalarB = pScalarB;

}

void HazardUnit::ImmSel(bit *pImmSel){
	apImmSel = pImmSel;

}

void HazardUnit::RegAddress(bit *pRa, bit *pRb){
	apRa = pRa;
	apRb = pRb;

}

void HazardUnit::Mode(bit *pMode){
	apMode = pMode;

}

void HazardUnit::VectorInput(bit *pVectorA, bit *pVectorB){
	apVectorA = pVectorA;
	apVectorB = pVectorB;

}

void HazardUnit::DataMem(bit *pDataMem){
	apDataMem = pDataMem;

}

void HazardUnit::ScalarDataExe(bit *pScalarDataExe){
	apScalarDataExe = pScalarDataExe;

}

void HazardUnit::DataWb(bit *pDataWb){
	apDataWb = pDataWb;

}

void HazardUnit::VectorDataExe(bit *pVectorDataExe){
	apVectorDataExe = pVectorDataExe;

}

void HazardUnit::RcMem(bit *pRcMem){
	apRcMem = pRcMem;

}

void HazardUnit::RcExe(bit *pRcExe){
	apRcExe = pRcExe;

}

void HazardUnit::RcWb(bit *pRcWb){
	apRcWb = pRcWb;

}

void HazardUnit::ModeMem(bit *pModeMem){
	apModeMem = pModeMem;

}

void HazardUnit::ModeExe(bit *pModeExe){
	apModeExe = pModeExe;

}

void HazardUnit::ModeWb(bit *pModeWb){
	apModeWb = pModeWb;

}

bit *HazardUnit::VectorOutA(void){
	return apVectorOutA;

}

bit *HazardUnit::VectorOutB(void){
	return apVectorOutB;

}

bit *HazardUnit::ScalarOutA(void){
	return apScalarOutA;

}

bit *HazardUnit::ScalarOutB(void){
	return apScalarOutB;

}

void HazardUnit::Width(int width){
	aWidth = width;

}

void HazardUnit::Initialize(void){
	apScalarOutA = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apScalarOutA, 0, aWidth);
	apScalarOutB = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apScalarOutB, 0, aWidth);

	apVectorOutA = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apVectorOutA, 0, aWidth);
	apVectorOutB = (bit *) malloc(sizeof(bit)*aWidth);
	memset(apVectorOutB, 0, aWidth);

}

void HazardUnit::Run(void){
	aRun = true;
	if (aRun) {
		if (apMode[1] == 0 && apMode[0] == 1) { // Actual inst Scalar - Scalar
			if (apRa[0] == apRcExe[0] &&
				apRa[1] == apRcExe[1] &&
				apRa[2] == apRcExe[2] &&
				apRa[3] == apRcExe[3] &&
				apMode[0] == apModeExe[15] &&
				apMode[1] == apModeExe[16] &&
				apModeExe[9] != 1){
				//printf(">> Caso Ra, adelanto de Exe\n");
				//BaseHelper::PrintBin(apScalarDataExe, aWidth);
				memcpy(apScalarOutA, apScalarDataExe, aWidth); // Forward register

			} else if (apRa[0] == apRcMem[0] &&
						apRa[1] == apRcMem[1] &&
						apRa[2] == apRcMem[2] &&
						apRa[3] == apRcMem[3] &&
						apMode[0] == apModeMem[15] &&
						apMode[1] == apModeMem[16] &&
						apModeMem[9] != 1){
				//printf(">> Caso Ra, adelanto de Mem\n");
				//BaseHelper::PrintBin(apDataWb, aWidth);
				memcpy(apScalarOutA, apDataMem, aWidth); // Forward register

			} else if (apRa[0] == apRcWb[0] &&
						apRa[1] == apRcWb[1] &&
						apRa[2] == apRcWb[2] &&
						apRa[3] == apRcWb[3] &&
						apMode[0] == apModeWb[15] &&
						apMode[1] == apModeWb[16] &&
						apModeWb[9] != 1){
				//printf(">> Caso Ra, adelanto de Wb\n");
				//BaseHelper::PrintBin(apDataMem, aWidth);
				memcpy(apScalarOutA, apDataWb, aWidth); // Forward register

			} else {
				//printf(">> Caso Ra, No adelanta\n");
				memcpy(apScalarOutA, apScalarA, aWidth); // No Forward register

			}

			if (apRb[0] == apRcExe[0] &&
				apRb[1] == apRcExe[1] &&
				apRb[2] == apRcExe[2] &&
				apRb[3] == apRcExe[3] &&
				apMode[0] == apModeExe[15] &&
				apMode[1] == apModeExe[16] &&
				apModeExe[9] != 1 &&
				apImmSel[0] != 1){
				//printf(">> Caso Rb, adelanto de Exe\n");
				//BaseHelper::PrintBin(apScalarDataExe, aWidth);
				memcpy(apScalarOutB, apScalarDataExe, aWidth); // Forward register

			} else if (apRb[0] == apRcMem[0] &&
						apRb[1] == apRcMem[1] &&
						apRb[2] == apRcMem[2] &&
						apRb[3] == apRcMem[3] &&
						apMode[0] == apModeMem[15] &&
						apMode[1] == apModeMem[16] &&
						apModeMem[9] != 1 &&
						apImmSel[0] != 1){
				//printf(">> Caso Rb, adelanto de Mem\n");
				//BaseHelper::PrintBin(apDataWb, aWidth);
				memcpy(apScalarOutB, apDataMem, aWidth); // Forward register

			} else if (apRb[0] == apRcWb[0] &&
						apRb[1] == apRcWb[1] &&
						apRb[2] == apRcWb[2] &&
						apRb[3] == apRcWb[3] &&
						apMode[0] == apModeWb[15] &&
						apMode[1] == apModeWb[16] &&
						apModeWb[9] != 1 &&
						apImmSel[0] != 1){
				//printf(">> Caso Rb, adelanto de Wb\n");
				//BaseHelper::PrintBin(apDataMem, aWidth);
				memcpy(apScalarOutB, apDataWb, aWidth); // Forward register

			} else {
				//printf(">> Caso Rb, No adelanta\n");
				memcpy(apScalarOutB, apScalarB, aWidth); // No Forward register

			}
		} else if (apMode[1] == 1 && apMode[0] == 0) { // Actual inst Vector - Vector
			//printf("Vector - Vector, not yet\n");
			// Not handled
			memcpy(apVectorOutA, apVectorA, aWidth); // No Forward register
			memcpy(apVectorOutB, apVectorB, aWidth); // No Forward register

		} else if (apMode[1] == 1 && apMode[0] == 1) { // Actual inst Vector - Scalar
			//printf("Vector - Scalar, not yet\n");
			// Not handled
			memcpy(apVectorOutA, apVectorA, aWidth); // No Forward register
			memcpy(apScalarOutA, apScalarA, aWidth); // No Forward register
			memcpy(apVectorOutB, apVectorB, aWidth); // No Forward register
			

			// Only Rb is used in Vector-Scalar inst
			if (apRb[0] == apRcExe[0] &&
				apRb[1] == apRcExe[1] &&
				apRb[2] == apRcExe[2] &&
				apRb[3] == apRcExe[3] &&
				apModeExe[15] == 1 &&
				apModeExe[16] == 0 &&
				apModeExe[9] != 1){
				//printf(">> Caso Rb, adelanto de Exe\n");
				//BaseHelper::PrintBin(apScalarDataExe, aWidth);
				memcpy(apScalarOutB, apScalarDataExe, aWidth); // Forward register

			} else if (apRb[0] == apRcMem[0] &&
						apRb[1] == apRcMem[1] &&
						apRb[2] == apRcMem[2] &&
						apRb[3] == apRcMem[3] &&
						apModeMem[15] == 1 &&
						apModeMem[16] == 0 &&
						apModeMem[9] != 1){
				//printf(">> Caso Rb, adelanto de Mem\n");
				//BaseHelper::PrintBin(apDataWb, aWidth);
				memcpy(apScalarOutB, apDataMem, aWidth); // Forward register

			} else if (apRb[0] == apRcWb[0] &&
						apRb[1] == apRcWb[1] &&
						apRb[2] == apRcWb[2] &&
						apRb[3] == apRcWb[3] &&
						apModeWb[15] == 1 &&
						apModeWb[16] == 0 &&
						apModeWb[9] != 1){
				//printf(">> Caso Rb, adelanto de Wb\n");
				//BaseHelper::PrintBin(apDataMem, aWidth);
				memcpy(apScalarOutB, apDataWb, aWidth); // Forward register

			} else {
				//printf(">> Caso Rb, No adelanta\n");
				memcpy(apScalarOutB, apScalarB, aWidth); // No Forward register

			}

		}
	}

}