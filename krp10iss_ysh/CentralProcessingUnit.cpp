#include "CentralProcessingUnit.h"
#include "Utils.h"

/**
	Lifecycles
*/
CentralProcessingUnit::CentralProcessingUnit() {
	registers[0] = { 0, };
	instructionRegisterByte[0] = { ' ', };
	instructionRegisterWord[0] = { ' ',};
	programCounter = 0;
}

CentralProcessingUnit::~CentralProcessingUnit() {

}