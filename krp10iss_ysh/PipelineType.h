#include "krp10iss_ysh.h"

interface FetchFromProgramMemoryUtils {

	/// <summary>
	/// FileService�� ����� �Է����� ��� binary ������ ����� memory����
	/// ����cpu �� PC���� ���� 4���� ����Ʈ�� uint32_t�������� ��ȯ�޽��ϴ�.
	/// ����Ʈ char���� ��Ʋ �ε�� ����� ����Ʈ�� ���ĵ� �� ��ȯ�˴ϴ�.
	/// ���� �� int�� �ڷ�� InstructionSetProcess::fetchInstructionFromProgramMemory(uint32_t opcode)�� �Ű������� ���޵Ǿ�
	/// 16������ ǥ���� 1����Ʈ�� �� 8��. 8����Ʈ�� �����Ǿ��� �����Դϴ�.
	/// </summary>
	/// <param name="pc"></param>
	/// <returns>uint32_t</returns>
	virtual uint32_t convertBinaryCharToByte() = 0;
};

/// <summary>
/// decode�� ���� utils
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
	/// TODO : ���α׷� �޸𸮿��� ���� PC���� ����� programMemory�� word fetch
	///		FileServiceType::convertBinaryCharToByte()�� ����մϴ�.
	///		programMemory���� ���� pc���� ���� 4����Ʈ�� �� 8����Ʈ�� �ش��ϴ� 16���� ������ �Ű������� �޽��ϴ�.
	/// </summary>
	/// <param name="operationCode"></param>
	virtual void fetchInstructionFromProgramMemory() = 0;

	/// <summary> 
	/// TODO : Convert 8bits -> 32bits(WORD) in Register  
	///		DecoderUtils�� �Լ����� �̿��� �� �Լ� fetchInstructionFromProgramMemory() �� ���� ���� opcode 8�ڸ� 16���� ��Ʈ����
	///		2������ ��ȯ�ؼ� 32bits == 1 WORD ������ Ȯ���մϴ�.
	///		32������ Ȯ���� ������ Ư�� opcode�� � ALU�� ������ �����ϴ��� Ư�� bits�� ������ �ľ��ϱ� �� decode�����Դϴ�.
	///		���������ο��� ���� ������ ���� ���� �۾��Դϴ�.
	///</summary>
	virtual void decode() = 0;

	/// <summary>
	/// TODO : Decode opcde from InstructionRegister(32bits)
	///		current PC���� ���� fetch�� Instruction���� ��� ������ ������ �� instruction���κ��� opcode�� decode�մϴ�.
	///		8����Ʈ�� 32������ instruction���� decode�� ��, opcode�� ���� ��� ALU������ Execute�ؾ��� �� �����ϵ��� �����߽��ϴ�.
	/// </summary>
	virtual int dataFetch() = 0;

	/// <summary>
	/// TODO : Execute instruction & write result.
	///		dataFetch�� ���� ���� opcode�� �� ���� �´� ������ ������ �� �����մϴ�.
	///		write�� ���ұ��� ����ֽ��ϴ�.
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