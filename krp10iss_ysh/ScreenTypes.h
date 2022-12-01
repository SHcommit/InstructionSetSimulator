#include "krp10iss_ysh.h"

interface ISSTestCpuStateScreenType {
	virtual void ISSTestShowCurrentPC() = 0;
	virtual void ISSTestShowCurrentByteOperationCode(uint32_t opCode) = 0;
	virtual void ISSTestShowCurrentByteToBinary() = 0;
	virtual void ISSTestShowCurrentWordOpcode() = 0;
	virtual void ISSTestShowInputAllInfo() = 0;
	virtual void ISSTestShowInputBinaryInfo() = 0;
};

interface DefualtScreenType {
public:
	/// <summary>
	///   instructionSetSimulator의 초기 정보를 화면에 출력합니다.
	/// </summary>
	virtual void instructionSetSimulatorInitialView() = 0;

};

interface CpuStateScreenType {
	/// <summary>
	/// 현재 pc에 대한 모든 register 상태를 보여줍니다.
	/// </summary>
	virtual void showCurrentAllRegisterState() = 0;

	/// <summary>
	/// 사용자에게 instructionSetSimulator process에서 사용 가능한 process 명령어를 보여줍니다.
	/// </summary>
	virtual void helpIssProcessCommendMannuel() = 0;
	/// <summary>
	/// 현재 GeneralPurposedRegisters의 모든 값을 출력합니다.
	/// </summary>
	virtual void showGeneralPurposedRegistersState() = 0;
	/// <summary>
	/// 현재 pc상태를 출력합니다.
	/// </summary>
	virtual void showProgramCounterState() = 0;

	/// <summary>
	/// current pc value에 따라 fetch된 instruciton의 16진수 8bits를 출력합니다.
	/// </summary>
	virtual void showInstructionStateWithByte() = 0;
};
