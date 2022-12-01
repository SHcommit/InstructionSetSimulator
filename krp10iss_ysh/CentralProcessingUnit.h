#include "krp10iss_ysh.h"
#include "Utils.h"

#pragma once


#ifndef __CentralProcessingUnit
#define __CentralProcessingUnit

/**
* #CentralProcessingUnit : cpu입니다.
*
* @Param registers : GeneralPurposeRegister
* @Param programCounter : Current PC state
* @Param instructionRegisterByte : 수행해야 할 Instruction Byte로 저장
* @Param instructionRegisterWord : 수행해야 할 Instruction 32bits로 저장
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
