#include "krp10iss_ysh.h"

interface FileServiceType {
public:

	/// <summary>
	/// �Է� ������ ���̳ʸ� ������ ������Ʈ�� �����ɴϴ�.
	/// FileService�� memory�� �����մϴ�.
	/// ���� �̰����� 4����Ʈ�� fetch�۾��� ���� instruction�� �����ɴϴ�.
	/// </summary>
	virtual void fetchInputBinaryFile() = 0;

	/// <summary>
	/// Instruction ������ ���� ���� ����� ���Ϸ� �����մϴ�.
	/// </summary>
	virtual void writeBinaryStramToFile() = 0;

	/// <summary>
	/// Instruction ���� ����� �������Ͽ� ����ϱ� ���� �����մϴ�.
	/// </summary>
	/// <param name="value"></param>
	virtual void executedInstructionResult(int value) = 0;
};