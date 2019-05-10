//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 10/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <VectorAlu.hpp>

void VectorAlu::Selector(bit *pSel){
	aLane1.Selector(pSel);
	aLane2.Selector(pSel);
	aLane3.Selector(pSel);
	aLane4.Selector(pSel);

}

void VectorAlu::OperA(bit *pOperA){
	aLane1.OperA(pOperA);
	aLane2.OperA(pOperA+aLaneWidth);
	aLane3.OperA(pOperA+2*aLaneWidth);
	aLane4.OperA(pOperA+3*aLaneWidth);

}

void VectorAlu::OperB(bit *pOperB){
	aLane1.OperB(pOperB);
	aLane2.OperB(pOperB+aLaneWidth);
	aLane3.OperB(pOperB+2*aLaneWidth);
	aLane4.OperB(pOperB+3*aLaneWidth);

}

void VectorAlu::ImmB(bit *pImmB){
	aLane1.ImmB(pImmB);
	aLane2.ImmB(pImmB);
	aLane3.ImmB(pImmB);
	aLane4.ImmB(pImmB);

}

void VectorAlu::Width(int width){
	aWidth = width;
	aLaneWidth = width / 4;
	aLane1.Width(aLaneWidth);
	aLane2.Width(aLaneWidth);
	aLane3.Width(aLaneWidth);
	aLane4.Width(aLaneWidth);

}

void VectorAlu::SelectorOpB(bit *pSelOpB){
	aLane1.SelectorOpB(pSelOpB);
	aLane2.SelectorOpB(pSelOpB);
	aLane3.SelectorOpB(pSelOpB);
	aLane4.SelectorOpB(pSelOpB);

}

bit *VectorAlu::Result(void){
	apLane1Result = aLane1.Result();
	apLane2Result = aLane2.Result();
	apLane3Result = aLane3.Result();
	apLane4Result = aLane4.Result();
	return apResult;

}

void VectorAlu::SelectorWidth(int width){
	aLane1.SelectorWidth(width);
	aLane2.SelectorWidth(width);
	aLane3.SelectorWidth(width);
	aLane4.SelectorWidth(width);

}

void VectorAlu::Initialize(void){
	apResult = (bit *) malloc(sizeof(bit)*aWidth);
	aLane1.Initialize();
	aLane2.Initialize();
	aLane3.Initialize();
	aLane4.Initialize();

}

void VectorAlu::Run(void){
	aLane1.RunMutex();
	aLane2.RunMutex();
	aLane3.RunMutex();
	aLane4.RunMutex();
	memcpy(apResult, apLane1Result, aLaneWidth);
	memcpy(apResult+aLaneWidth, apLane2Result, aLaneWidth);
	memcpy(apResult+2*aLaneWidth, apLane3Result, aLaneWidth);
	memcpy(apResult+3*aLaneWidth, apLane4Result, aLaneWidth);
	
}