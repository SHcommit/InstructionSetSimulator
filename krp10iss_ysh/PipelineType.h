#include "krp10iss_ysh.h"

interface FetchFromProgramMemoryUtils {

	/// <summary>
	/// FileService에 저장된 입력파일 모든 binary 정보가 저장된 memory에서
	/// 현재cpu 의 PC값에 따라 4개의 바이트를 uint32_t형식으로 반환받습니다.
	/// 바이트 char값은 리틀 인디언 방식의 바이트로 정렬된 후 반환됩니다.
	/// 추후 이 int형 자료는 InstructionSetProcess::fetchInstructionFromProgramMemory(uint32_t opcode)의 매개변수로 전달되어
	/// 16진수로 표현된 1바이트가 총 8개. 8바이트로 구성되어질 예정입니다.
	/// </summary>
	/// <param name="pc"></param>
	/// <returns>uint32_t</returns>
	virtual uint32_t convertBinaryCharToByte() = 0;
};

/// <summary>
/// decode를 위한 utils
/// </summary>
interface DecoderUtils {
	virtual string intToString(uint32_t operationCode) = 0;
	virtual char* stringToCharArray(const char* operationCode) = 0;	
	virtual void convertByteOpCodeToWord() = 0;
	virtual string decimalToBinary(uint32_t decimal, int bits) = 0;
	virtual string binaryOcodeDecodeInInstruction() = 0;
	virtual int binaryOpcodeToDecimal(int startIndex, int length) = 0;
};

interface PipelineType : public DecoderUtils, public FetchFromProgramMemoryUtils {

	/// <summary>
	/// TODO : 프로그램 메모리에서 현재 PC값을 사용해 programMemory의 word fetch
	///		FileServiceType::convertBinaryCharToByte()를 사용합니다.
	///		programMemory에서 현재 pc값에 따라 4바이트씩 총 8바이트에 해당하는 16진수 값들을 매개변수로 받습니다.
	/// </summary>
	/// <param name="operationCode"></param>
	virtual void fetchInstructionFromProgramMemory() = 0;

	/// <summary> 
	/// TODO : Convert 8bits -> 32bits(WORD) in Register  
	///		DecoderUtils의 함수들을 이용해 위 함수 fetchInstructionFromProgramMemory() 를 통해 얻어온 opcode 8자리 16진수 비트들을
	///		2진수로 변환해서 32bits == 1 WORD 단위로 확장합니다.
	///		32비츠로 확장한 이유는 특정 opcode가 어떤 ALU의 연산을 수행하는지 특정 bits의 역할을 파악하기 한 decode과정입니다.
	///		파이프라인에서 빠른 수행을 위한 사전 작업입니다.
	///</summary>
	virtual void decode() = 0;

	/// <summary>
	/// TODO : Decode opcde from InstructionRegister(32bits)
	///		current PC값을 통해 fetch한 Instruction에서 어느 연산을 수행할 지 instruction으로부터 opcode를 decode합니다.
	///		8바이트에 32비츠의 instruction으로 decode한 후, opcode를 통해 어느 ALU연산을 Execute해야할 지 결정하도록 구성했습니다.
	/// </summary>
	virtual int dataFetch() = 0;

	/// <summary>
	/// TODO : Execute instruction & write result.
	///		dataFetch를 통해 얻은 opcode와 그 값에 맞는 연산을 수행한 후 저장합니다.
	///		write의 역할까지 담겨있습니다.
	/// </summary>
	virtual void execution(int opcode) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// TODO : 
	///		1. Fetch from program Memory to InstructionRegsiterByte(IR)
	///		2. Decode from InstructionRegisterByte to InstructionRegisterWord
	///		3. DataFetch InstructionRegister. get opcode
	///		4. Execution Instruction by operand
	/// </summary>
	virtual void pipelining() = 0;


	/// <summary>
	/// TODO : all instruction execute..
	/// </summary>
	virtual void pipeliningAllExecuted() = 0;

};