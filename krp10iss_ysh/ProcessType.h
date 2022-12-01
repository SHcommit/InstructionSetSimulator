#include "krp10iss_ysh.h"

interface ProcessType {
	/// <summary>
	/// instructionSetSimulator�� �����ϴ� ���� �����Դϴ�.
	/// ������� �Է°��� ���� �̺�Ʈ�� ����˴ϴ�.
	/// </summary>
	virtual void issProcess() = 0;
	/// <summary>
	/// ������� �Է°��� �����մϴ�.
	/// </summary>
	virtual char tappedUserKeyboard() = 0;

	/// <summary>
	/// ������� �Է°� �������� �����մϴ�.
	/// </summary>
	virtual void checkUserInputFinished() = 0;

};