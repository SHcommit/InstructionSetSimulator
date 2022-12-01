#pragma once

#ifndef __CentralProcessingUnitUtils
#define __CentralProcessingUnitUtils

/**
* TODO: This is condition code can be used in branch instructions
* 
* @param NV: Never
* @param AL: Always
* @param EQ: Equal zero
* @param NE: Not equal zero
* @param GE: Greater or equal than zero
* @param LT: Less than zero
*/
enum Condition {
	NV,
	AL,
	EQ,
	NE,
	GE,
	LT
};

#endif // !__CentralProcessingUnitUtils
