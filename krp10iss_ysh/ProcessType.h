#include "krp10iss_ysh.h"

interface ProcessType {
	/// <summary>
	/// instructionSetSimulator가 동작하는 메인 루프입니다.
	/// 사용자의 입력값에 따라 이벤트가 실행됩니다.
	/// </summary>
	virtual void issProcess() = 0;
	/// <summary>
	/// 사용자의 입력값을 감지합니다.
	/// </summary>
	virtual char tappedUserKeyboard() = 0;

	/// <summary>
	/// 사용자의 입력값 끝났는지 감지합니다.
	/// </summary>
	virtual void checkUserInputFinished() = 0;

};