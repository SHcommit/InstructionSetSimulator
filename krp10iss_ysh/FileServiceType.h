#include "krp10iss_ysh.h"

interface FileServiceType {
public:

	/// <summary>
	/// 입력 파일인 바이너리 파일을 프로젝트로 가져옵니다.
	/// FileService의 memory에 저장합니다.
	/// 추후 이곳에서 4바이트씩 fetch작업을 통해 instruction을 가져옵니다.
	/// </summary>
	virtual void fetchInputBinaryFile() = 0;

	/// <summary>
	/// Instruction 연산이 끝난 이후 결과를 파일로 저장합니다.
	/// </summary>
	virtual void writeBinaryStramToFile() = 0;

	/// <summary>
	/// Instruction 연산 결과를 덤프파일에 출력하기 위해 저장합니다.
	/// </summary>
	/// <param name="value"></param>
	virtual void executedInstructionResult(int value) = 0;
};