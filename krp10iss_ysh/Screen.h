#include "krp10iss_ysh.h"
#include "ScreenTypes.h"

#pragma once
#ifndef OutputConsole
#define OutputConsole

class Screen : public CpuStateScreenType, public DefualtScreenType, public ISSTestCpuStateScreenType {
public:

	/* Lifecycles */
	Screen();
	~Screen();

	/* DefualtScreenType Helpers */
	virtual void instructionSetSimulatorInitialView();

	/* CpuStateScreenType Helpers */
	virtual void showCurrentAllRegisterState();
	virtual void helpIssProcessCommendMannuel();
	virtual void showGeneralPurposedRegistersState();
	virtual void showProgramCounterState();
	virtual void showInstructionStateWithByte();

	/* ISSTestCpuStateScreenType Helpers */
	virtual void ISSTestShowCurrentPC();
	virtual void ISSTestShowCurrentByteOperationCode(uint32_t opCode);
	virtual void ISSTestShowCurrentByteToBinary();
	virtual void ISSTestShowCurrentWordOpcode();
	virtual void ISSTestShowInputAllInfo();	
	virtual void ISSTestShowInputBinaryInfo();

};

#endif // !OutputConsole
