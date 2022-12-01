#include "krp10iss_ysh.h"
#include "Utils.h"

#pragma once


#ifndef __CentralProcessingUnit
#define __CentralProcessingUnit

/**
* #CentralProcessingUnit : cpu�Դϴ�.
*
* @Param registers : GeneralPurposeRegister
* @Param programCounter : Current PC state
* @Param instructionRegisterByte : �����ؾ� �� Instruction Byte�� ����
* @Param instructionRegisterWord : �����ؾ� �� Instruction 32bits�� ����
*/
typedef struct CentralProcessingUnit {
public:
	/* Properties */
	int registers[WORD];
	uint32_t programCounter;
	char instructionRegisterByte[BYTE+2];
	char instructionRegisterWord[WORD];

	/* Lifecycles */
	CentralProcessingUnit();
	~CentralProcessingUnit();

}CPU;



#endif // !__CentralProcessingUnit
