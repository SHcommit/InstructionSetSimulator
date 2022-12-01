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
	///   instructionSetSimulator�� �ʱ� ������ ȭ�鿡 ����մϴ�.
	/// </summary>
	virtual void instructionSetSimulatorInitialView() = 0;

};

interface CpuStateScreenType {
	/// <summary>
	/// ���� pc�� ���� ��� register ���¸� �����ݴϴ�.
	/// </summary>
	virtual void showCurrentAllRegisterState() = 0;

	/// <summary>
	/// ����ڿ��� instructionSetSimulator process���� ��� ������ process ��ɾ �����ݴϴ�.
	/// </summary>
	virtual void helpIssProcessCommendMannuel() = 0;
	/// <summary>
	/// ���� GeneralPurposedRegisters�� ��� ���� ����մϴ�.
	/// </summary>
	virtual void showGeneralPurposedRegistersState() = 0;
	/// <summary>
	/// ���� pc���¸� ����մϴ�.
	/// </summary>
	virtual void showProgramCounterState() = 0;

	/// <summary>
	/// current pc value�� ���� fetch�� instruciton�� 16���� 8bits�� ����մϴ�.
	/// </summary>
	virtual void showInstructionStateWithByte() = 0;
};
